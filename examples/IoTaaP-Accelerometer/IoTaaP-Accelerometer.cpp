#include "IoTaaP.h"

IoTaaP iotaap;

void setup()
{
  iotaap.oled.init();
}

void loop()
{
  // Read accelerometer values
  accelerometer acc = iotaap.accelerometer.getRaw();
  // Display accelerometer values
  iotaap.oled.showText("X: " + String(acc.x) + "\nY: " + String(acc.y) + "\nZ: " + String(acc.z));
  delay(100);
}