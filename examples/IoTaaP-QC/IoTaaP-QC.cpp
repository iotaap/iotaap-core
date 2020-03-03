/**
 * @file IoTaaP-QC.cpp
 * @brief IoTaaP Quality Control code
 * @version 0.1
 * 
 */

#include <IoTaaP.h>

IoTaaP iotaap; // IoTaaP library

void setup()
{
  iotaap.oled.init();
  iotaap.oled.showText("QC TEST");
  delay(500);
  iotaap.buzzer.initBuzzer();
  iotaap.oled.showText("1. Buzzer\n500ms tone");
  iotaap.buzzer.generateTone(1000, false, 500);
  iotaap.oled.showText("2. DAC\nPIN 26\n1.65V");
  iotaap.dac.set(127);
  delay(1000);
  iotaap.oled.showText("3. ADC\nPIN 27\n" + String(iotaap.adc.getVoltage(27)));
  delay(1000);
  iotaap.oled.showText("4. Hall\n" + String(iotaap.hall.read()));
  delay(1000);
  iotaap.oled.showText("5. Serial\nprintln: TEST OK");
  iotaap.serial.init(115200);
  iotaap.serial.printLn("TEST OK");
  delay(500);
  iotaap.oled.showText("6. LED1\n100ms/3 blinks");
  iotaap.misc.blinkOnboardLed(ONBOARD_LED1, 100, 3);
  iotaap.oled.showText("7. LED2\n100ms/3 blinks");
  iotaap.misc.blinkOnboardLed(ONBOARD_LED2, 100, 3);
  iotaap.oled.showText("8. Press BUT1");
  while (!iotaap.misc.getBUT1())
    ;
  iotaap.oled.showText("OK");
  while (iotaap.misc.getBUT1())
    ;
  iotaap.oled.showText("9. Press BUT2");
  while (!iotaap.misc.getBUT2())
    ;
  iotaap.oled.showText("OK");
  while (iotaap.misc.getBUT2())
    ;
  delay(500);
  iotaap.oled.showText("QC PASS!");
}

void loop()
{
}