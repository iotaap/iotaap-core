#include "IoTaaP_DAC.h"


IoTaaP_DAC::IoTaaP_DAC(){

}

/**
 * @brief Sets onboard DAC output
 * 
 * @param value DAC value (0-255)
 */
void IoTaaP_DAC::setDAC(uint8_t value)
{
    dacWrite(DAC2, value);
}

