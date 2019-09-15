#include "IoTaaP_MQTT.h"

/**
 * @brief Construct a new IoTaaP_MQTT::IoTaaP_MQTT object
 * 
 */
IoTaaP_MQTT::IoTaaP_MQTT()
{
}

/**
 * @brief Connects to the MQTT server on a desired port
 * 
 * @param clientID Client ID that will be used in communication
 * @param server MQTT server IP address or URL
 * @param port MQTT port of the server
 * @param user Optional MQTT instance username
 * @param password Optional MQTT instance password 
 * @return true if successfully connected
 * @return false if there was a problem
 */
bool IoTaaP_MQTT::connect(const char *clientID, const char *server, uint16_t port, MQTT_CALLBACK_SIGNATURE, const char *user, const char *password)
{
    this->_mqttclientID = clientID;
    this->_mqttuser = user;
    this->_mqttpassword = password;

    this->_mqttPubSub = PubSubClient(this->_wifiClient);

    this->_mqttPubSub.setServer(server, port);
    this->_mqttPubSub.setCallback(callback);

    if (!this->_mqttPubSub.connected())
    {
        return this->_reconnectMQTT();
    }
    return true;
}

/**
 * @brief Reconnect to MQTT server 
 * 
 * @return true if succesfully connected
 * @return false it there was a problem
 */
bool IoTaaP_MQTT::_reconnectMQTT()
{
    int timeoutCounter = 0;

    // Loop until we're reconnected
    while (!this->_mqttPubSub.connected())
    {
        // Attempt to connect
        if (this->_mqttuser == '\0')
        {
            if (this->_mqttPubSub.connect(this->_mqttclientID))
            {
                return true;
            }
        }
        else
        {
            if (this->_mqttPubSub.connect(this->_mqttclientID, this->_mqttuser, this->_mqttpassword))
            {
                return true;
            }
        }

        delay(500);
        timeoutCounter = (timeoutCounter + 1) / 2;
        if (timeoutCounter >= MQTT_TIMEOUT)
        {
            return false;
        }
        timeoutCounter++;
    }
    return true;
}

/**
 * @brief Keep the connection with MQTT alive, and reconnect if lost. Should be put in the main loop
 * 
 * @return uint16_t Returns 2 if succesfully reconnected, returns 0 if there was a problem and returns 1 if already connected
 */
uint16_t IoTaaP_MQTT::keepAlive()
{
    if (!this->_mqttPubSub.connected())
    {
        if (this->_reconnectMQTT())
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }
    this->_mqttPubSub.loop();
    return 1;
}

/**
 * @brief Publish payload to the specified topic
 * 
 * @param topic MQTT topic
 * @param payload MQTT topic payload
 * @return true if successfully connected
 * @return false if there was a problem
 */
bool IoTaaP_MQTT::publish(const char *topic, const char *payload)
{
    return this->_mqttPubSub.publish(topic, payload);
}

/**
 * @brief Subscribe to the MQTT topic
 * 
 * @param topic Topic name
 */
void IoTaaP_MQTT::subscribe(const char *topic)
{
    this->_mqttPubSub.subscribe(topic);
}
