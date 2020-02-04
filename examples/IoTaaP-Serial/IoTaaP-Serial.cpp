#include <IoTaaP.h>

IoTaaP iotaap;

void setup()
{
  // Initialize IoTaaP serial port with 115200 baud rate  
  iotaap.serial.init(115200);
  // Print line to the serial port
  iotaap.serial.printLn("IoTaaP Serial Communication");
  // Delay for 1 second
  delay(1000);
}

void loop()
{
  // If character is received, send it back
  if(iotaap.serial.isAvailable()){
    iotaap.serial.writeChar(iotaap.serial.readChar());
  }
}