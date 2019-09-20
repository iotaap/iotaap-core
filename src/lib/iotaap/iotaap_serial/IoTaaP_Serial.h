#ifndef __IOTAAP_SERIAL_H__
#define __IOTAAP_SERIAL_H__

#include "lib/iotaap/iotaap_misc/IoTaaP_Misc.h"

class IoTaaP_Serial
{
public:
    IoTaaP_Serial();

    void init(unsigned long baud);
    void printLn(String string);
    size_t writeChar(char ch);
    String getString();
    String getStringUntil(char delimiter);
    int isAvailable();
    int readChar();

private:
};

#endif