#include "IoTaaP_Buzzer.h"

IoTaaP_Buzzer::IoTaaP_Buzzer(){

}

/**
 * @brief Initializes onboard buzzer, must be called before buzzer is used
 * 
 */
void IoTaaP_Buzzer::initBuzzer()
{
    ledcSetup(0, 127, 8);
    ledcAttachPin(ONBOARD_BUZZER, 0);
}

/**
 * @brief Generates tone on the buzzer
 * 
 * @param freq Tone frequency
 * @param forever If TRUE, tone will be reporduced until buzzerStop() is called
 * @param durationMs Tone duration, will be ignored if 'forever' is true
 */
void IoTaaP_Buzzer::buzzerTone(int freq, bool forever, int durationMs)
{
    ledcWriteTone(0, freq);
    if (!forever)
    {
        delay(durationMs);
        this->buzzerStop();
    }
}

/**
 * @brief Stops and detaches onboard buzzer. Buzzer must be initialized first.
 * 
 */
void IoTaaP_Buzzer::buzzerStop()
{
    ledcDetachPin(ONBOARD_BUZZER);
    pinMode(ONBOARD_BUZZER, OUTPUT);
    digitalWrite(ONBOARD_BUZZER, LOW);
}