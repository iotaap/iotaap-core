#define ENABLE_JSON

#include "IoTaaP.h"

IoTaaP iotaap; // IoTaaP library

void callback(char *topic, byte *message, unsigned int length)
{
  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    messageTemp += (char)message[i];
  }

  if (String(topic) == "ledstatus/led1")
  {
    if (messageTemp == "on")
    {
      iotaap.misc.setPin(ONBOARD_LED1);
    }
    else if (messageTemp == "off")
    {
      iotaap.misc.clearPin(ONBOARD_LED1);
    }
  }
}

DynamicJsonDocument doc(1024);

void setup()
{
  iotaap.wifi.connect("SSID", "PASSWORD");

  iotaap.mqtt.connect("iotaap_client", "farmer.cloudmqtt.com", 00000, callback, false, "USERNAME", "PASSWORD");
  iotaap.mqtt.subscribe("ledstatus/led1");
}

void loop()
{
  iotaap.mqtt.keepAlive();

  accelerometer acc = iotaap.accelerometer.getRaw();

  doc["x"] = acc.x;
  doc["y"] = acc.y;
  doc["z"] = acc.z;

  char accJson[255];

  serializeJson(doc, accJson);

  iotaap.mqtt.publish("iotaap/accelerometer", accJson, false);

  delay(200);
}
