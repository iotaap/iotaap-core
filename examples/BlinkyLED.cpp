#include "IoTaaP.h"

#define LED 26

IoTaaP iotaap;

void setup()
{
  // Define output pin
  iotaap.misc.makePinOutput(LED);
}

void loop()
{
  // Turn the LED on by making voltage level HIGH
  iotaap.misc.setPin(LED);
  // Wait for 0.5 seconds
  delay(500);
  // Turn the LED off by making voltage level LOW
  iotaap.misc.clearPin(LED);
  // Wait for 0.5 seconds
  delay(500);
}