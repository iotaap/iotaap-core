#include "IoTaaP_Hall.h"

IoTaaP_Hall::IoTaaP_Hall(){

}

/**
 * @brief Reads onboard hall sensor value
 * 
 * @return int Value for HALL sensor (without LNA)
 */
int IoTaaP_Hall::readHall()
{
    return hallRead();
}