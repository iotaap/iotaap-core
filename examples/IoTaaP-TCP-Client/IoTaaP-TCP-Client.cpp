#include <IoTaaP.h>

IoTaaP iotaap;

void setup()
{
  // Init OLED
  iotaap.oled.init();
  // Connect to the WiFi AP
  iotaap.wifi.connect("SSID", "PASSWORD");
  // Connect to the TCP server
  iotaap.tcp.connect("YOUR-PC-IP-ADDRESS", 5656);
}

void loop()
{
  char data[255];
  // Read string from TCP server
  iotaap.tcp.readString('\0').toCharArray(data, 255);
  // Show received string on the OLED
  iotaap.oled.showText(data);
  // Send received string back to the server
  iotaap.tcp.send(data);

  // If string equals to ON, blink onboard LED1
  if (String(data) == "ON")
  {
    iotaap.misc.blinkOnboardLed(ONBOARD_LED1);
  }
}