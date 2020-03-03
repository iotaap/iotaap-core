#include <IoTaaP.h>
#include <ESP32CAN.h>
#include <CAN_config.h>

// Defining CAN configuration variable
CAN_device_t CAN_cfg;

IoTaaP iotaap;

void setup()
{
  iotaap.serial.init(9600);

  CAN_cfg.speed = CAN_SPEED_1000KBPS; // CAN baud rate
  CAN_cfg.tx_pin_id = GPIO_NUM_26;    // CAN TX pin
  CAN_cfg.rx_pin_id = GPIO_NUM_27;    // CAN RX pin

  // CAN receiving queue
  CAN_cfg.rx_queue = xQueueCreate(10, sizeof(CAN_frame_t));
  // CAN Initialisation
  ESP32Can.CANInit();
}

void loop()
{
  CAN_frame_t rx_frame;
  // Get next CAN frame from queue
  if (xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS) == pdTRUE)
  {

    // Process data
    if (rx_frame.FIR.B.FF == CAN_frame_std)
      iotaap.serial.printLn("New standard frame");
    else
      iotaap.serial.printLn("New extended frame");

    if (rx_frame.FIR.B.RTR == CAN_RTR)
      printf(" RTR from 0x%08x, DLC %d\r\n", rx_frame.MsgID, rx_frame.FIR.B.DLC); // Using printf in order to format received data
    else
    {
      printf(" from 0x%08x, DLC %d\n", rx_frame.MsgID, rx_frame.FIR.B.DLC); // Using printf in order to format received data
      // Converting received character to uppercase and returning back to sender
      for (int i = 0; i < 8; i++)
      {
        if (rx_frame.data.u8[i] >= 'a' && rx_frame.data.u8[i] <= 'z')
        {
          rx_frame.data.u8[i] = rx_frame.data.u8[i] - 32;
        }
      }
    }
    // Send response
    ESP32Can.CANWriteFrame(&rx_frame);
  }
}