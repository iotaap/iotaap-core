#include "IoTaaP_Hall.h"

/**
 * @brief Construct a new IoTaaP_Hall::IoTaaP_Hall object
 * 
 */
IoTaaP_Hall::IoTaaP_Hall()
{
}

/**
 * @brief Reads onboard hall sensor value
 * 
 * @return int Value for HALL sensor (without LNA)
 */
int IoTaaP_Hall::read()
{
    return hallRead();
}