#ifndef __IOTAAP_TCP_H__
#define __IOTAAP_TCP_H__

#include "lib/iotaap/iotaap_misc/IoTaaP_Misc.h"

class IoTaaP_TCP{
    public:

    IoTaaP_TCP();

    WiFiClient openTCPconnection(const char *host, uint16_t port);
    void sendTCP(const char *payload);
    String readTCPstring(const char delimiter);
    void closeTCP();

    private:
    WiFiClient _tcpWifiClient;
};

#endif