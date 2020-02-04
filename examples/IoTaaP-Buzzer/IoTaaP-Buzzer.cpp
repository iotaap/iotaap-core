#include <IoTaaP.h>

IoTaaP iotaap;

void setup()
{
  // Initialize buzzer
  iotaap.buzzer.initBuzzer();
  // Generate tone with 2400Hz frequency that will last for 300mS
  iotaap.buzzer.generateTone(2400, false, 300);
}

void loop()
{
  for (int i = 0; i <= 20000; i = i + 10)
  {
    iotaap.buzzer.initBuzzer();
    iotaap.buzzer.generateTone(i, false, 10);
  }
  // Detach buzzer
  iotaap.buzzer.stopTone();
}