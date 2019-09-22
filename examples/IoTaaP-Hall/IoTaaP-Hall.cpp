#include "IoTaaP.h"

IoTaaP iotaap;

void setup()
{
  iotaap.oled.init();
}

void loop()
{
  iotaap.oled.showText(String(iotaap.hall.read()));
  delay(200);
}