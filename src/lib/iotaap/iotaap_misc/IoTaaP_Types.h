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

/**
 * @brief Structure that contains accelerometer values
 * 
 */
struct accelerometer
{
    uint16_t x;
    uint16_t y;
    uint16_t z;
};

#endif