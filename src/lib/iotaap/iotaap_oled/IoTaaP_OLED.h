#ifndef __IOTAAP_OLED_H__
#define __IOTAAP_OLED_H__

#include "lib/iotaap/iotaap_misc/IoTaaP_Misc.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "lib/iotaap/iotaap_oled/iotaap_splash.h"

class IoTaaP_OLED
{
public:
    IoTaaP_OLED();

    void init();
    void showText(String text, int x = 0, int y = 0);
    void displayBitmap(int16_t x, int16_t y, const uint8_t bitmap[], uint16_t color);
    void setBrightness(uint8_t perc);

private:
    Adafruit_SSD1306 _display;
    void _setContrast(int contr);
};

#endif