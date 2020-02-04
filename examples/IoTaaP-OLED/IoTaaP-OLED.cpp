#include <IoTaaP.h>

IoTaaP iotaap;

void setup()
{
  // Initialize OLED
  iotaap.oled.init();
  // Show some text
  iotaap.oled.showText("Countdown", 40, 30);
  delay(1500);
}

void loop()
{

  for (int i = 10; i >= 0; i--)
  {
    iotaap.oled.showText(String(i), 60, 32);
    delay(500);
  }
  // Display IoTaaP logo
  iotaap.oled.displayBitmap(0, 0, iotaap_splash_128x64, 1);
  while (1);
}
