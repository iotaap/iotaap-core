#include "IoTaaP_MQTT.h"

/**
 * @brief Construct a new IoTaaP_MQTT::IoTaaP_MQTT object
 * 
 */
IoTaaP_MQTT::IoTaaP_MQTT()
{
    this->_intervalCounter = 0;
}

/**
 * @brief Connects to the MQTT server on a desired port
 * 
 * @param clientID Client ID that will be used in communication
 * @param server MQTT server IP address or URL
 * @param port MQTT port of the server
 * @param secure If true MQTTS will be used and ca_cert is required, MQTT will be used by default
 * @param user Optional MQTT instance username
 * @param password Optional MQTT instance password 
 * @param ca_cert CA Certificate or Root certificate used to verify SSH connection
 * @return true if successfully connected
 * @return false if there was a problem
 */
bool IoTaaP_MQTT::connect(const char *clientID, const char *server, uint16_t port, MQTT_CALLBACK_SIGNATURE, bool secure, const char *user, const char *password, const char *ca_cert)
{

    this->_mqttclientID = clientID;
    this->_mqttuser = user;
    this->_mqttpassword = password;

    if (secure)
    {
        this->_wifiClientSecure.setCACert(ca_cert);
        this->_mqttPubSub = PubSubClient(this->_wifiClientSecure);
    }
    else
    {
        this->_mqttPubSub = PubSubClient(this->_wifiClient);
    }

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
 * @brief Subscribes to IoTaaP API topics and enables Serial function
 * 
 * @param serialBaud Optional baud rate if Serial is used. Default 115200.
 */
void IoTaaP_MQTT::enableApi(unsigned long serialBaud)
{
    this->subscribe("api/#");
    this->_iotaapSerial.init(serialBaud);
}

/**
 * @brief API function that will publish IoTaaP input states to the topic 'api/transfer'. Almost non-blocking.
 * 
 * @param interval Time in ms between two state readings. Default 10ms.
 */
void IoTaaP_MQTT::apiLoop(int interval)
{
    DynamicJsonDocument _doc(1024);
    this->keepAlive();

    delay(1);
    this->_intervalCounter++;
    if (_intervalCounter >= interval)
    {
        _intervalCounter = 0;

        _doc["device"] = this->_mqttclientID;

        _doc["data"]["onboard"]["but1"] = this->_iotaapMisc.getBUT1();
        _doc["data"]["onboard"]["but2"] = this->_iotaapMisc.getBUT2();

        _doc["data"]["digital"]["2"] = this->_iotaapMisc.getPin(2);
        _doc["data"]["digital"]["4"] = this->_iotaapMisc.getPin(4);
        _doc["data"]["digital"]["12"] = this->_iotaapMisc.getPin(12);
        _doc["data"]["digital"]["13"] = this->_iotaapMisc.getPin(13);
        _doc["data"]["digital"]["14"] = this->_iotaapMisc.getPin(14);
        _doc["data"]["digital"]["15"] = this->_iotaapMisc.getPin(15);
        _doc["data"]["digital"]["16"] = this->_iotaapMisc.getPin(16);
        _doc["data"]["digital"]["17"] = this->_iotaapMisc.getPin(17);
        _doc["data"]["digital"]["26"] = this->_iotaapMisc.getPin(26);
        _doc["data"]["digital"]["27"] = this->_iotaapMisc.getPin(27);
        _doc["data"]["digital"]["32"] = this->_iotaapMisc.getPin(32);
        _doc["data"]["digital"]["33"] = this->_iotaapMisc.getPin(33);
        _doc["data"]["digital"]["34"] = this->_iotaapMisc.getPin(34);
        _doc["data"]["digital"]["35"] = this->_iotaapMisc.getPin(35);

        _doc["data"]["analog"]["16"] = this->_iotaapMisc.adc.getValue(16);
        _doc["data"]["analog"]["17"] = this->_iotaapMisc.adc.getValue(17);
        _doc["data"]["analog"]["32"] = this->_iotaapMisc.adc.getValue(32);
        _doc["data"]["analog"]["33"] = this->_iotaapMisc.adc.getValue(33);
        _doc["data"]["analog"]["34"] = this->_iotaapMisc.adc.getValue(34);
        _doc["data"]["analog"]["35"] = this->_iotaapMisc.adc.getValue(35);

        char accJson[1024];

        serializeJson(_doc, accJson);

        this->_mqttPubSub.publish("api/transfer", accJson);
    }
}

/**
 * @brief Inner function to be used in MQTT callback as direct API listener on topic 'api/listen/<control_topic>'.
 * 
 * @param controlTopic Topic where control JSON is published
 * @param topic Callback topic parameter
 * @param message Callback message parameter
 * @param length Callback length parameter
 */
void IoTaaP_MQTT::callbackInnerFunction(String controlTopic, char *topic, byte *message, unsigned int length)
{
    String messageTemp;
    DynamicJsonDocument inputBuffer(1024);

    for (int i = 0; i < length; i++)
    {
        messageTemp += (char)message[i];
    }

    // Check if data is received on state layer
    if (String(topic) == "api/listen/" + controlTopic)
    {
        deserializeJson(inputBuffer, messageTemp);

        // Check if data type is serial
        if (inputBuffer.containsKey("serial"))
        {
            // Transfer data to serial
            this->_iotaapSerial.printLn(inputBuffer["serial"]["data"]);
        }
        // Check if data type is output
        if (inputBuffer.containsKey("output"))
        {
            // Make pin as output
            this->_iotaapPWM.disablePWM((int)inputBuffer["output"]["pin"]);
            this->_iotaapMisc.makePinOutput((int)inputBuffer["output"]["pin"]);
            // Check if pin is digital
            if (inputBuffer["output"]["type"] == "digital")
            {
                // Set or Clear the pin
                (int)inputBuffer["output"]["value"] ? this->_iotaapMisc.setPin((int)inputBuffer["output"]["pin"]) : this->_iotaapMisc.clearPin((int)inputBuffer["output"]["pin"]);
            }

            // Check if pin is analog
            if (inputBuffer["output"]["type"] == "analog")
            {
                // Set Analog value
                this->_iotaapPWM.setup(1, 5000, 16, (int)inputBuffer["output"]["pin"]);
                this->_iotaapPWM.set(1, (int)inputBuffer["output"]["value"]);
            }
        }
    }
}

/**
 * @brief Publish payload to the specified topic
 * 
 * @param topic MQTT topic
 * @param payload MQTT topic payload
 * @param retain Retain last message
 * @return true if successfully connected
 * @return false if there was a problem
 */
bool IoTaaP_MQTT::publish(const char *topic, const char *payload, boolean retain)
{
    return this->_mqttPubSub.publish(topic, payload, retain);
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
