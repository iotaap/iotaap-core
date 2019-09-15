#include "IoTaaP_PWM.h"

IoTaaP_PWM::IoTaaP_PWM(){

}

/**
 * @brief Setups the PWM channel, and attaches pin
 * 
 * @param channel PWM channel (1-15)
 * @param freq PWM Frequency
 * @param resolution PWM resolution (1-16)
 * @param pin PWM pin
 */
void IoTaaP_PWM::setupPWM(uint8_t channel, double freq, uint8_t resolution, uint8_t pin)
{
    ledcSetup(channel, freq, resolution);
    ledcAttachPin(pin, channel);
}

/**
 * @brief Sets PWM duty cycle to PWM channel. setupPWM() must be called before
 * 
 * @param channel Preset PWM channel
 * @param duty PWM duty cycle
 */
void IoTaaP_PWM::setPWM(uint8_t channel, uint32_t duty)
{
    ledcWrite(channel, duty);
}