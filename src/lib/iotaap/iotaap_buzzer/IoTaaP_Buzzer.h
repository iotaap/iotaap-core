#ifndef __IOTAAP_BUZZER_H__
#define __IOTAAP_BUZZER_H__

#include "lib/iotaap/iotaap_misc/IoTaaP_Misc.h"

class IoTaaP_Buzzer{
    public:
    
    IoTaaP_Buzzer();
        void initBuzzer();
    void buzzerTone(int freq = 1000, bool forever = false, int durationMs = 500);
    void buzzerStop();

    private:
};


#endif