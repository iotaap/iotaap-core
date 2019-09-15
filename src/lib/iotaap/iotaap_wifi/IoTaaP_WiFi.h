#ifndef __IOTAAP_WIFI_H__
#define __IOTAAP_WIFI_H__

#include "lib/iotaap/iotaap_misc/IoTaaP_Misc.h"

class IoTaaP_WiFi
{
public:
    IoTaaP_WiFi();

    wifiConnectionInfo connect(const char *ssid, const char *pass);
    int scan();
    String getScanned(uint8_t i);
    IPAddress openAP(const char *ssid, const char *password = NULL);

private:
};

#endif