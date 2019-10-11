#ifndef __IOTAAP_PWM_H__
#define __IOTAAP_PWM_H__

#include "lib/iotaap/iotaap_misc/IoTaaP_Misc.h"

class IoTaaP_PWM
{
public:
    IoTaaP_PWM();

    void setup(uint8_t channel, double freq, uint8_t resolution, uint8_t pin);
    void set(uint8_t channel, uint32_t duty);
    void disablePWM(uint8_t pin);

private:
};

#endif