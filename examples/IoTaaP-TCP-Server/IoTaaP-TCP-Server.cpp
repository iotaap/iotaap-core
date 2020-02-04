#include <IoTaaP.h>

IoTaaP iotaap;

void setup()
{
  // Init OLED
  iotaap.oled.init();
  // Connect to the WiFi AP
  iotaap.wifi.connect("SSID", "PASSWORD");
  // Show local IP address
  iotaap.oled.showText(WiFi.localIP().toString());
  // Start TCP server on port 344
  iotaap.wifiServer.begin(344);
}

void loop()
{
  // Check if client is requesting connection
  iotaap.wifiClient = iotaap.wifiServer.available();

  if (iotaap.wifiClient)
  {
    // Serve client while connected
    while (iotaap.wifiClient.connected())
    {

      while (iotaap.wifiClient.available() > 0)
      {
        char c = iotaap.wifiClient.read();
        iotaap.wifiClient.write(c);
      }

      delay(10);
    }
    // Close connection
    iotaap.wifiClient.stop();
  }
}