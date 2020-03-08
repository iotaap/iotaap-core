#ifndef __IOTAAP_MQTT_H__
#define __IOTAAP_MQTT_H__

#include "lib/iotaap/iotaap_misc/IoTaaP_Misc.h"
#include "WiFi.h"
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include "lib/iotaap/iotaap_misc/IoTaaP_Misc.h"
#include <ArduinoJson.h>
#include "lib/iotaap/iotaap_serial/IoTaaP_Serial.h"
#include "lib/iotaap/iotaap_pwm/IoTaaP_PWM.h"

#define MQTT_MAX_PACKET_SIZE 4096

class IoTaaP_MQTT
{
public:
    IoTaaP_MQTT();

    bool connect(const char *clientID, const char *server, uint16_t port, MQTT_CALLBACK_SIGNATURE, bool secure = false, const char *user = '\0', const char *password = '\0', const char *ca_cert = "");
    uint16_t keepAlive();
    bool publish(const char *topic, const char *payload, boolean retain);
    void subscribe(const char *topic);
    void callbackInnerFunction(String controlTopic, char *topic, byte *message, unsigned int length);

private:
    PubSubClient _mqttPubSub;
    bool _reconnectMQTT();
    int _intervalCounter;
    const char *_mqttclientID;
    const char *_mqttuser;
    const char *_mqttpassword;
    WiFiClientSecure _wifiClientSecure;
    WiFiClient _wifiClient;
    IoTaaP_Misc _iotaapMisc;
    IoTaaP_Serial _iotaapSerial;
    IoTaaP_PWM _iotaapPWM;
};

#endif