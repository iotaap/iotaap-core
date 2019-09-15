#ifndef __IOTAAP_SERIAL_H__
#define __IOTAAP_SERIAL_H__

#include "lib/iotaap/iotaap_misc/IoTaaP_Misc.h"

class IoTaaP_Serial{
    public:

    IoTaaP_Serial();

       void initSerial(unsigned long baud);
    void printlnSerial(String string);
    String getLnSerial();

    private:
};

#endif