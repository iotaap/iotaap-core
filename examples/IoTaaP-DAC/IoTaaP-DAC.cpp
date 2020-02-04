#include <IoTaaP.h>

IoTaaP iotaap;

void setup()
{
}

void loop()
{
  for (int i = 0; i <= 255; i++)
  {
    // Set DAC value
    iotaap.dac.set(i);
    delay(10);
  }
  for (int i = 255; i >= 0; i--)
  {
    iotaap.dac.set(i);
    delay(10);
  }
}