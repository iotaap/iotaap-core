#include <IoTaaP.h>

IoTaaP iotaap;

void setup()
{
  // Blink onboard LED
  iotaap.misc.blinkOnboardLed(ONBOARD_LED1, 100, 5);
  // Make P26 as input
  iotaap.misc.makePinInput(26);
  // Make P27 as output
  iotaap.misc.makePinOutput(27);
}

void loop()
{
  // Check if BUT1 is pressed and turn on LED1 if true
  if (iotaap.misc.getBUT1())
  {
    iotaap.misc.setPin(ONBOARD_LED1);
  }
  // If BUT1 is not pressed turn off LED1
  else
  {
    iotaap.misc.clearPin(ONBOARD_LED1);
  }
  // Check if BUT2 is pressed and turn on LED2 if true
  if (!iotaap.misc.getPin(ONBOARD_BUT2))
  {
    iotaap.misc.setPin(ONBOARD_LED2);
  }
  // If BUT2 is not pressed turn off LED2
  else
  {
    iotaap.misc.clearPin(ONBOARD_LED2);
  }
  // If battery percentage is < 5, put IoTaaP to sleep for 1 minute
  if (iotaap.misc.getBatteryPercentage() < 5)
  {
    iotaap.misc.sleep(60);
  }
}
