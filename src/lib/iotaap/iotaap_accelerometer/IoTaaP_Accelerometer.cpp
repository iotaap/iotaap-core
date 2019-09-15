#include "IoTaaP_Accelerometer.h"

IoTaaP_Accelerometer::IoTaaP_Accelerometer(){

}

/**
 * @brief Returns RAW (0-4095) values of accelerometer x,y,z axes
 * 
 * @return accelerometer Structure with x,y,z values
 */
accelerometer IoTaaP_Accelerometer::getAccelerometerRaw()
{
    accelerometer acc;

    acc.x = this->adc.getAnalogValue(ACCELEROMETER_X_PIN);
    acc.y = this->adc.getAnalogValue(ACCELEROMETER_Y_PIN);
    acc.z = this->adc.getAnalogValue(ACCELEROMETER_Z_PIN);

    return acc;
}