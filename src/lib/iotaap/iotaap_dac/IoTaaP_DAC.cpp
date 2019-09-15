#include "IoTaaP_DAC.h"

/**
 * @brief Construct a new IoTaaP_DAC::IoTaaP_DAC object
 * 
 */
IoTaaP_DAC::IoTaaP_DAC()
{
}

/**
 * @brief Sets onboard DAC output
 * 
 * @param value DAC value (0-255)
 */
void IoTaaP_DAC::set(uint8_t value)
{
    dacWrite(DAC2, value);
}
