#define ENABLE_KAI
#define ENABLE_BTSERIAL

#include "IoTaaP.h"
#include "lib/3rd_party/Servo/Servo.h"

IoTaaP iotaap; // IoTaaP library

void setup()
{
  iotaap.kai.init(16, 17, 4, 13); // Setup KAI robot servo pins
  iotaap.kai.home(); // Move servo motors to initial position
  iotaap.btSerial.begin("KAI"); // Open Bluetooth connection 
}

void loop()
{
  if (iotaap.btSerial.available()) // Check if data is available on serial receiver
  {
    if (iotaap.btSerial.read() == 'k') // Check if character 'k' is received
    {
      iotaap.kai.walk(12, 1, 0); // Walk if true
    }
  }
  delay(20);
}