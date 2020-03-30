#include "IoTaaP_WiFi.h"

/**
 * @brief Construct a new IoTaaP_WiFi::IoTaaP_WiFi object
 * 
 */
IoTaaP_WiFi::IoTaaP_WiFi()
{
}

/**
 * @brief Connects to the WiFi AP
 * 
 * @param ssid AP SSID
 * @param pass AP Password
 * @param restartOnFail System will reboot if WiFi connection fails
 * @return wifiConnectionInfo Returns structure containing status 1 and IP address if connected successfully, or status -1 and IP 0.0.0.0 if there was a problem
 */
wifiConnectionInfo IoTaaP_WiFi::connect(const char *ssid, const char *pass, bool restartOnFail)
{
    wifiConnectionInfo connectionInfo;
    int timeoutCounter = 0;
    WiFi.mode(WIFI_STA);
    WiFi.setHostname("localhost");
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1);
        timeoutCounter = timeoutCounter + 1;
        if (timeoutCounter >= WIFI_TIMEOUT)
        {
            connectionInfo.status = -1;
            connectionInfo.ipAddress = IPAddress(0, 0, 0, 0);
            if (restartOnFail)
            {
                ESP.restart();
            }
            return connectionInfo;
        }
    }

    connectionInfo.status = 1;
    connectionInfo.ipAddress = WiFi.localIP();

    return connectionInfo;
}

/**
 * @brief Scans for open WiFi networks and returns number of networks discovered
 * 
 * @return int Number of networks discovered
 */
int IoTaaP_WiFi::scan()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    return WiFi.scanNetworks();
}

/**
 * @brief Returns SSID of discovered network
 * 
 * @param i Specify from which network item want to get the information
 * @return String SSID string of the specified item on the networks scanned list
 */
String IoTaaP_WiFi::getScanned(uint8_t i)
{
    return WiFi.SSID(i);
}

/**
 * @brief Opens WiFi access point with provided credentials. If password is not provided AP will be open. AP IP: 192.168.8.1
 * 
 * @param ssid AP SSID
 * @param password AP Password (optional)
 * @return IPAddress Returns local IP address if successfully opened or empty IPAddress if not
 */
IPAddress IoTaaP_WiFi::openAP(const char *ssid, const char *password)
{
    WiFi.softAPConfig(IPAddress(192, 168, 8, 1), IPAddress(192, 168, 8, 100), IPAddress(255, 255, 255, 255));

    if (password == NULL)
    {
        if (WiFi.softAP(ssid))
        {
            return WiFi.softAPIP();
        }
    }
    else
    {
        if (WiFi.softAP(ssid, password))
        {
            return WiFi.softAPIP();
        }
    }

    return IPAddress();
}