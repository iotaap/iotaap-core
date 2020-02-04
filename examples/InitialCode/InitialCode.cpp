#include <IoTaaP.h>

IoTaaP iotaap;

void setup()
{
    // Blink onboard LED
    iotaap.misc.blinkOnboardLed(ONBOARD_LED1, 100, 5);
    // Initialize OLED
    iotaap.oled.init();
    // Show IoTaaP logo
    iotaap.oled.displayBitmap(0, 0, iotaap_splash_128x64, 1);
    // Keep logo for 2.2 seconds
    delay(2200);
    // Display message
    iotaap.oled.showText("Go forward, express\nyourself and start\nyour innovative\njourney today!");
}

void loop()
{
}
