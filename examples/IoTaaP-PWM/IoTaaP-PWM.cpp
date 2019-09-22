#include "IoTaaP.h"

IoTaaP iotaap;

void setup()
{
  // Configure PWM output
  iotaap.pwm.setup(1, 1000, 8, 26);
}

void loop()
{
  for (int i = 0; i <= 255; i++)
  {
    // Set PWM duty cycle
    iotaap.pwm.set(1, i);
    delay(10);
  }
  for (int i = 255; i >= 0; i--)
  {
    iotaap.pwm.set(1, i);
    delay(10);
  }
}