#ifndef __IOTAAP_KAI_H__
#define __IOTAAP_KAI_H__

#include "lib/iotaap/iotaap_misc/IoTaaP_Misc.h"
#include <Wire.h>
#include "lib/3rd_party/AdafruitServoDriver/Adafruit_PWMServoDriver.h"

class IoTaaP_Kai
{
public:
    IoTaaP_Kai();

    void init();
    void home();
    void walk(unsigned long T, uint16_t loops, uint16_t dir = 0);

private:

    Adafruit_PWMServoDriver _pwm;

    int _count1;
    int _count2;
    int _count3;
    int _count4;

    int _pos1;
    int _pos2;
    int _pos3;
    int _pos4;

    int _c1;
    int _c2;
    int _c3;
    int _c4;

    unsigned long _servoTime;
    int _executedLoops;
};

#endif