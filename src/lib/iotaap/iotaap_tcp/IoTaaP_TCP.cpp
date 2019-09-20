#include "IoTaaP_TCP.h"

/**
 * @brief Construct a new IoTaaP_TCP::IoTaaP_TCP object
 * 
 */
IoTaaP_TCP::IoTaaP_TCP()
{
}

/**
 * @brief Connects to the TCP server
 * 
 * @param host Host IP or DNS
 * @param port Host port
 * @return WiFiClient Returns configured WiFiClient object or empty object if there was a problem
 */
WiFiClient IoTaaP_TCP::connect(const char *host, uint16_t port)
{

    if (!this->_tcpWifiClient.connect(host, port))
    {
        return WiFiClient();
    }
    return this->_tcpWifiClient;
}

/**
 * @brief Sends payload to opened TCP connection
 * 
 * @param payload Payload to be sent
 */
void IoTaaP_TCP::send(const char *payload)
{
    this->_tcpWifiClient.print(payload);
}

/**
 * @brief Reads string from TCP until delimiter is received
 * 
 * @param delimiter Delimiter character
 * @return String Returns received payload
 */
String IoTaaP_TCP::readString(const char delimiter)
{
    return this->_tcpWifiClient.readStringUntil(delimiter);
}

/**
 * @brief Closes opened TCP connection
 * 
 */
void IoTaaP_TCP::close()
{
    this->_tcpWifiClient.stop();
}