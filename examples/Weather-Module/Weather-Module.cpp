#include <IoTaaP.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

IoTaaP iotaap;

Adafruit_BME280 bme; // I2C

void showMeasurements()
{
  iotaap.serial.printLn("Temperature: " + String(bme.readTemperature(), 2) + " *C");
  iotaap.serial.printLn("Pressure: " + String(bme.readPressure() / 100.0F, 2) + " hPa");
  iotaap.serial.printLn("Altitude: " + String(bme.readAltitude(SEALEVELPRESSURE_HPA), 2) + " m");
  iotaap.serial.printLn("Humidity: " + String(bme.readHumidity(), 2) + " %");

  iotaap.serial.printLn("");
}

void setup()
{
  iotaap.serial.init(9600);

  if (!bme.begin(BME280_ADDRESS_ALTERNATE))
  { // 0x76 is the default address on Weather & SD Module
    iotaap.serial.printLn("Could not find a valid BME280 sensor!");
    while (1)
      ;
  }

  iotaap.serial.printLn("");
}

void loop()
{
  showMeasurements();
  delay(1000);
}