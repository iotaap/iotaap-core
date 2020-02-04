#ifndef __IOTAAP_TYPES_H__
#define __IOTAAP_TYPES_H__
#include <Arduino.h>

/**
 * @brief Structure that contains WiFi connection status and IP address
 * 
 */
struct wifiConnectionInfo
{
    int status;
    IPAddress ipAddress;
};

#endif