#ifndef __IOTAAP_MQTT_H__
#define __IOTAAP_MQTT_H__

#include "lib/iotaap/iotaap_misc/IoTaaP_Misc.h"
#include "WiFi.h"
#include "lib/3rd_party/PubSubClient/PubSubClient.h"
#include <WiFiClientSecure.h>

class IoTaaP_MQTT
{
public:
    IoTaaP_MQTT();

    bool connect(const char *clientID, const char *server, uint16_t port, MQTT_CALLBACK_SIGNATURE, bool secure = false, const char *user = '\0', const char *password = '\0', const char *ca_cert = "");
    uint16_t keepAlive();
    bool publish(const char *topic, const char *payload);
    void subscribe(const char *topic);

private:
    PubSubClient _mqttPubSub;
    bool _reconnectMQTT();
    const char *_mqttclientID;
    const char *_mqttuser;
    const char *_mqttpassword;
    WiFiClientSecure _wifiClientSecure;
    WiFiClient _wifiClient;
};

#endif