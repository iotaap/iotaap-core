#include "IoTaaP_ADC.h"

/**
 * @brief Construct a new IoTaaP_ADC::IoTaaP_ADC object
 * 
 */
IoTaaP_ADC::IoTaaP_ADC()
{
    analogSetSamples(ADC_SAMPLES);
}

/**
 * @brief Reads analog value from analog pin
 * 
 * @param pin Andalog pin to read value from
 * @return unsigned long 12bit analog value
 */
unsigned long IoTaaP_ADC::getValue(int pin)
{
    return analogRead(pin);
}

/**
 * @brief Returns voltage (V) from A/D reading
 * 
 * @param reading RAW A/D reading (0-4095);
 * @return double Calculated calibrated voltage
 */
double IoTaaP_ADC::getVoltage(int reading)
{
    if (reading < 1 || reading > 4095)
        return 0;
    return (-0.000000000000016 * pow(reading, 4) + 0.000000000118171 * pow(reading, 3) - 0.000000301211691 * pow(reading, 2) + 0.001109019271794 * reading + 0.034143524634089);
}