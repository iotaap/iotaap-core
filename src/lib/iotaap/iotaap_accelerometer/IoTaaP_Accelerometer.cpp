#include "IoTaaP_Accelerometer.h"

/**
 * @brief Construct a new IoTaaP_Accelerometer::IoTaaP_Accelerometer object
 * 
 */
IoTaaP_Accelerometer::IoTaaP_Accelerometer()
{
}

/**
 * @brief Returns RAW (0-4095) values of accelerometer x,y,z axes
 * 
 * @return accelerometer Structure with x,y,z values
 */
accelerometer IoTaaP_Accelerometer::getRaw()
{
    accelerometer acc;

    acc.x = this->_adc.getValue(ACCELEROMETER_X_PIN);
    acc.y = this->_adc.getValue(ACCELEROMETER_Y_PIN);
    acc.z = this->_adc.getValue(ACCELEROMETER_Z_PIN);

    return acc;
}