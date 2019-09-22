#include <IoTaaP.h>
#include <SparkFunTSL2561.h>

IoTaaP iotaap;
SFE_TSL2561 light;

boolean gain;    // Gain setting, 0 = X1, 1 = X16;
unsigned int ms; // Integration ("shutter") time in milliseconds

double lux;   // Resulting lux value
boolean good; // True if sensor is saturated

void setup()
{
  // Initialize the Serial port:
  iotaap.serial.init(115200);
  iotaap.serial.printLn("TSL2561 example");

  // Initialize the TSL2561
  light.begin();

  // If gain = false (0), device is set to low gain (1X)
  // If gain = high (1), device is set to high gain (16X)
  gain = 0;

  // If time = 0, integration will be 13.7ms
  // If time = 1, integration will be 101ms
  // If time = 2, integration will be 402ms
  unsigned char time = 2;

  // setTiming() will set the third parameter (ms) to the
  // requested integration time in ms (this will be useful later):
  iotaap.serial.printLn("Set timing...");
  light.setTiming(gain, time, ms);

  // To start taking measurements, power up the sensor:
  iotaap.serial.printLn("Powerup...");
  light.setPowerUp();
}

void loop()
{
  delay(ms);
  
  unsigned int data0, data1;

  if (light.getData(data0, data1))
  {

    // Perform lux calculation:
    good = light.getLux(gain, ms, data0, data1, lux);

    // Print out the results:
    iotaap.serial.printLn("lux: ");
    iotaap.serial.printLn(String(lux));
    if (good)
      iotaap.serial.printLn("GOOD");
    else
      iotaap.serial.printLn("BAD");
  }
  else
  {
    iotaap.serial.printLn("Error");
  }
}
