#ifndef __IOTAAP_MISC_H__
#define __IOTAAP_MISC_H__

#include <Arduino.h>
#include <Wire.h>
#include "WiFi.h"
#include "IoTaaP_Defines.h"
#include "IoTaaP_Types.h"
#include "lib/iotaap/iotaap_adc/IoTaaP_ADC.h"

class IoTaaP_Misc
{
public:
    IoTaaP_Misc();

    IoTaaP_ADC adc;

    void blinkOnboardLed(int LED, int interval = 100, int loops = 1);
    void makePinOutput(int pin);
    void makePinInput(int pin);
    void setPin(int pin);
    void clearPin(int pin);
    bool getBUT1();
    bool getBUT2();
    double getBatteryPercentage();
    void sleep(int seconds = 1);
    void restart();

private:
};

#endif