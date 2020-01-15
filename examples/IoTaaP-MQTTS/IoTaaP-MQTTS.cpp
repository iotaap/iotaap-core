#define ENABLE_JSON

#include "IoTaaP.h"

IoTaaP iotaap; // IoTaaP library

// Let's Encrypt Cross Signed certificate
// More info about Let's Encrypt Chain of Trust can be found here: https://letsencrypt.org/certificates/
// We are using this certificate: https://letsencrypt.org/certs/trustid-x3-root.pem.txt
const char *CA_cert = "-----BEGIN CERTIFICATE-----\n"
                      "MIIDSjCCAjKgAwIBAgIQRK+wgNajJ7qJMDmGLvhAazANBgkqhkiG9w0BAQUFADA/\n"
                      "MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n"
                      "DkRTVCBSb290IENBIFgzMB4XDTAwMDkzMDIxMTIxOVoXDTIxMDkzMDE0MDExNVow\n"
                      "PzEkMCIGA1UEChMbRGlnaXRhbCBTaWduYXR1cmUgVHJ1c3QgQ28uMRcwFQYDVQQD\n"
                      "Ew5EU1QgUm9vdCBDQSBYMzCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEB\n"
                      "AN+v6ZdQCINXtMxiZfaQguzH0yxrMMpb7NnDfcdAwRgUi+DoM3ZJKuM/IUmTrE4O\n"
                      "rz5Iy2Xu/NMhD2XSKtkyj4zl93ewEnu1lcCJo6m67XMuegwGMoOifooUMM0RoOEq\n"
                      "OLl5CjH9UL2AZd+3UWODyOKIYepLYYHsUmu5ouJLGiifSKOeDNoJjj4XLh7dIN9b\n"
                      "xiqKqy69cK3FCxolkHRyxXtqqzTWMIn/5WgTe1QLyNau7Fqckh49ZLOMxt+/yUFw\n"
                      "7BZy1SbsOFU5Q9D8/RhcQPGX69Wam40dutolucbY38EVAjqr2m7xPi71XAicPNaD\n"
                      "aeQQmxkqtilX4+U9m5/wAl0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNV\n"
                      "HQ8BAf8EBAMCAQYwHQYDVR0OBBYEFMSnsaR7LHH62+FLkHX/xBVghYkQMA0GCSqG\n"
                      "SIb3DQEBBQUAA4IBAQCjGiybFwBcqR7uKGY3Or+Dxz9LwwmglSBd49lZRNI+DT69\n"
                      "ikugdB/OEIKcdBodfpga3csTS7MgROSR6cz8faXbauX+5v3gTt23ADq1cEmv8uXr\n"
                      "AvHRAosZy5Q6XkjEGB5YGV8eAlrwDPGxrancWYaLbumR9YbK+rlmM6pZW87ipxZz\n"
                      "R8srzJmwN0jP41ZL9c8PDHIyh8bwRLtTcm1D9SZImlJnt1ir/md2cXjbDaJWFBM5\n"
                      "JDGFoqgCWjBH4d1QB7wCCZAA62RjYJsWvIjJEubSfZGL+T0yjWW06XyxV3bqxbYo\n"
                      "Ob8VZRzI9neWagqNdwvYkQsEjgfbKbYK7p2CNTUQ\n"
                      "-----END CERTIFICATE-----\n";

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

  iotaap.mqtt.connect("iotaap_client", "iotaap.cloud", 8883, callback, true, "USERNAME", "PASSWORD", CA_cert);
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

  iotaap.mqtt.publish("iotaap/accelerometer", accJson, true);

  delay(200);
}
