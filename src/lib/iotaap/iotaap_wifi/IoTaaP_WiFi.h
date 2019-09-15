#ifndef __IOTAAP_WIFI_H__
#define __IOTAAP_WIFI_H__

#include "lib/iotaap/iotaap_misc/IoTaaP_Misc.h"

class IoTaaP_WiFi{
    public:

    IoTaaP_WiFi();

wifiConnectionInfo connectToWifi(const char *ssid, const char *pass);
    int scanWiFi();
    String getScannedWiFi(uint8_t i);
    IPAddress openWiFiAP(const char *ssid, const char *password = NULL);

    private:
};

#endif