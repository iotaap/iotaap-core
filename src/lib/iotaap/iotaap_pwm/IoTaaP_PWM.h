#ifndef __IOTAAP_PWM_H__
#define __IOTAAP_PWM_H__

#include "lib/iotaap/iotaap_misc/IoTaaP_Misc.h"

class IoTaaP_PWM{
    public:

    IoTaaP_PWM();

    void setupPWM(uint8_t channel, double freq, uint8_t resolution, uint8_t pin);
    void setPWM(uint8_t channel, uint32_t duty);

    private:
};

#endif