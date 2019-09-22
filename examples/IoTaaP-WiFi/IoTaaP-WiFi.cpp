#include "IoTaaP.h"

IoTaaP iotaap;

void setup()
{
  // Init oled and show text
  iotaap.oled.init();
  iotaap.oled.showText("Scanning...");

  // Scann WiFi AP's and return number of discovered
  int numOfAP = iotaap.wifi.scan();

  // Create list of available networks
  String networks = "Available networks:\n\n";

  for (int i = 0; i < numOfAP; i++)
  {
    networks += String(i + 1) + ". " + iotaap.wifi.getScanned(i) + "\n";
  }

  // Show discovered networks
  iotaap.oled.showText(networks);
  delay(3000);

  // Connect to the first network discovered
  iotaap.oled.showText("Connecting to: " + iotaap.wifi.getScanned(0));

  // Convert String type SSID to char type SSID
  char SSID[64];
  iotaap.wifi.getScanned(0).toCharArray(SSID, 64);

  // Declare wifiInfo structure
  wifiConnectionInfo wifiInfo;

  // Connect to the SSID with Password (must be valid password)
  wifiInfo = iotaap.wifi.connect(SSID, "password");
  delay(1000);

  // Check if IoTaaP is connected to the WiFi network
  if (wifiInfo.status == 1)
  {
    // Display IP address if successfully connected
    iotaap.oled.showText("Connected!\n\nIP: " + wifiInfo.ipAddress.toString());
  }
  else
  {
    // Display message if there was a problem
    iotaap.oled.showText("There was a problem");
  }
}

void loop()
{
  delay(500);
}