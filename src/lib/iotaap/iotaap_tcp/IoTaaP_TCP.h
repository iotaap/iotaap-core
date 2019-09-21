#ifndef __IOTAAP_TCP_H__
#define __IOTAAP_TCP_H__

#include "lib/iotaap/iotaap_misc/IoTaaP_Misc.h"
#include "WiFi.h"

class IoTaaP_TCP
{
public:
    IoTaaP_TCP();

    WiFiClient connect(const char *host, uint16_t port);
    void send(const char *payload);
    String readString(const char delimiter);
    void close();

private:
    WiFiClient _tcpWifiClient;
};

#endif