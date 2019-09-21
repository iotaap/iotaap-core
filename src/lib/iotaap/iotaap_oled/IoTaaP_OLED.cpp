#include "IoTaaP_OLED.h"

/**
 * @brief Construct a new IoTaaP_OLED::IoTaaP_OLED object
 * 
 */
IoTaaP_OLED::IoTaaP_OLED() : _display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1)
{
}

/**
 * @brief Initializes integrated OLED
 * 
 */
void IoTaaP_OLED::init()
{
    this->_display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    this->_display.clearDisplay();
    this->_display.display();
}

/**
 * @brief Sets OLED brightness
 * 
 * @param perc Brightness percentage (0-100)
 */
void IoTaaP_OLED::setBrightness(uint8_t perc)
{
    if (perc >= 100)
    {
        perc = 100;
    }
    if (perc <= 0)
    {
        perc = 1;
    }

    this->_display.ssd1306_command(SSD1306_SETCONTRAST);
    uint8_t _perc = (uint8_t)255 * ((float)perc / 100);
    this->_display.ssd1306_command(_perc);
}

/**
 * @brief Shows text on integrated OLED. OLED must be initialized first
 * 
 * @param text Text to be printed
 * @param x Text location on x coordinate
 * @param y Text location on y coordinate
 */
void IoTaaP_OLED::showText(const String text, int x, int y)
{
    this->_display.clearDisplay();
    this->_display.setTextSize(1);
    this->_display.setTextColor(WHITE);
    this->_display.setCursor(x, y);
    this->_display.println(text);
    this->_display.display();
}

/**
 * @brief Displays bitmap on OLED. initOLED() must be called before
 * 
 * @param x Start X coordinate (usually 0)
 * @param y Start Y coordinate (Usually 0)
 * @param bitmap Bitmap to show
 * @param color Bitmap color (usually 1)
 */
void IoTaaP_OLED::displayBitmap(int16_t x, int16_t y, const uint8_t bitmap[], uint16_t color)
{
    this->_display.drawBitmap(x, y, bitmap, SCREEN_WIDTH, SCREEN_HEIGHT, color);
    this->_display.display();
}