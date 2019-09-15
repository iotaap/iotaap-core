#ifndef __IOTAAP_ACCELEROMETER_H__
#define __IOTAAP_ACCELEROMETER_H__

#include "lib/iotaap/iotaap_misc/IoTaaP_Misc.h"
#include "lib/iotaap/iotaap_adc/IoTaaP_ADC.h"

class IoTaaP_Accelerometer
{
public:
    IoTaaP_Accelerometer();

    IoTaaP_ADC adc;
    accelerometer getRaw();

private:
};

#endif