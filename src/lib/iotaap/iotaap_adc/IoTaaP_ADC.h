#ifndef __IOTAAP_ADC_H__
#define __IOTAAP_ADC_H__

#include <Arduino.h>
#include "lib/iotaap/iotaap_misc/IoTaaP_Defines.h"

class IoTaaP_ADC
{
public:
    IoTaaP_ADC();

    unsigned long getValue(int pin);
    double getVoltage(int reading);

private:
};

#endif