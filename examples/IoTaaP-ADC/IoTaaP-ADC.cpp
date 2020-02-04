#include <IoTaaP.h>

IoTaaP iotaap;

void setup()
{
  iotaap.oled.init();
}

void loop()
{
  // Get RAW value from pin 26
  uint16_t value = iotaap.adc.getValue(26);
  // Convert RAW value to voltage
  double voltage = iotaap.adc.getVoltage(value);
  // Show data on the OLED
  iotaap.oled.showText("RAW: " + String(value) + "\nVoltage: " + String(voltage));
  delay(100);
}