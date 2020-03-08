#include "IoTaaP_Misc.h"

/**
 * @brief Construct a new IoTaaP_Misc::IoTaaP_Misc object
 * 
 */
IoTaaP_Misc::IoTaaP_Misc()
{
    this->makePinOutput(ONBOARD_LED1);
    this->makePinOutput(ONBOARD_LED2);
    this->makePinInput(ONBOARD_BUT1);
    this->makePinInput(ONBOARD_BUT2);
}

/**
 * @brief Blinks onboard LED for given interval and repeats loop 
 * 
 * @param LED Onboard LED, can be ONBOARD_LED1 or ONBOARD_LED2
 * @param interval Time in ms between LED states
 * @param loops Number of loops to repeat
 */
void IoTaaP_Misc::blinkOnboardLed(int LED, int interval, int loops)
{
    for (int i = 0; i < loops; i++)
    {
        this->setPin(LED);
        delay(interval);
        this->clearPin(LED);
        delay(interval);
    }
}

/**
 * @brief Defines pin as OUTPUT, must be called before setting pin state
 * 
 * @param pin Pin to be defined as input
 */
void IoTaaP_Misc::makePinOutput(int pin)
{
    pinMode(pin, OUTPUT);
}

/**
 * @brief Defines pin as INPUT, must be called before reading pin state
 * 
 * @param pin Pin to be defined as input
 */
void IoTaaP_Misc::makePinInput(int pin)
{
    if (pin != ONBOARD_BUT1)
    {
        pinMode(pin, INPUT);
    }
    else
    {
        pinMode(pin, INPUT_PULLUP);
    }
}

/**
 * @brief Sets the pin (HIGH state)
 * 
 * @param pin Pin to set
 */
void IoTaaP_Misc::setPin(int pin)
{
    digitalWrite(pin, HIGH);
}

/**
 * @brief Clears the pin (LOW state)
 * 
 * @param pin Pin to be cleared 
 */
void IoTaaP_Misc::clearPin(int pin)
{
    digitalWrite(pin, LOW);
}

/**
 * @brief Reads state of Button1 
 * 
 * @return true if pressed
 * @return false if not pressed
 */
bool IoTaaP_Misc::getBUT1()
{
    return !digitalRead(ONBOARD_BUT1);
}

/**
 * @brief Reads state of Button2 
 * 
 * @return true if pressed
 * @return false if not pressed
 */
bool IoTaaP_Misc::getBUT2()
{
    return !digitalRead(ONBOARD_BUT2);
}

bool IoTaaP_Misc::getPin(int pin)
{
    return digitalRead(pin);
}

/**
 * @brief Returns current battery percentage
 * 
 * @return double Battery percentage
 */
double IoTaaP_Misc::getBatteryPercentage()
{
    float perc = round(((this->adc.getVoltage(this->adc.getValue(BATSENS_PIN)) * 2) / 4.2) * 100);
    if (perc > 100)
        perc = 100;
    if (perc < 0)
        perc = 0;
    return perc;
}

/**
 * @brief Deep sleep with timer Wake Up after defined time in seconds (default 1);
 * 
 * @param seconds Time in seconds
 */
void IoTaaP_Misc::sleep(int seconds)
{
    esp_sleep_enable_timer_wakeup(seconds * 1000000);
    esp_deep_sleep_start();
}

/**
 * @brief Restarts IoTaaP
 * 
 */
void IoTaaP_Misc::restart()
{
    esp_restart();
}