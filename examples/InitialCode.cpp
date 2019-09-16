#include "IoTaaP.h"

IoTaaP iotaap;

void setup()
{
    // Blink onboard LED
    iotaap.misc.blinkOnboardLed(ONBOARD_LED1, 100, 5);
    // Initialize OLED
    iotaap.oled.init();
    // Show IoTaaP logo
    iotaap.oled.displayBitmap(0, 0, iotaap_splash_128x64, 1);
    // Initialize onboard buzzer
    iotaap.buzzer.initBuzzer();
    // Generate tones
    iotaap.buzzer.generateTone(2300, false, 200);
    iotaap.buzzer.generateTone(1000, false, 800);
    // Detach buzzer
    iotaap.buzzer.stopTone();
    // Keep logo for 2.2 seconds
    delay(2200);
    // Display message
    iotaap.oled.showText("Go forward, express\nyourself and start\nyour innovative\njourney today!");
}

void loop()
{
}
