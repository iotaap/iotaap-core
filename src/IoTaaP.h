/*
 * IoTaaP - Internet of Things as a Platform
 * Connectivity platform for rapid development
 * 
 * IoTaaP Team <contact@iotaap.io>
 * https://www.iotaap.io
 * 
 */

#ifndef __IOTAAP_H__
#define __IOTAAP_H__

// Libs
#include "lib/iotaap/iotaap_misc/IoTaaP_Misc.h"
#include "lib/iotaap/iotaap_oled/IoTaaP_OLED.h"
#include "lib/iotaap/iotaap_mqtt/IoTaaP_MQTT.h"
#include "lib/iotaap/iotaap_wifi/IoTaaP_WiFi.h"
#include "lib/iotaap/iotaap_tcp/IoTaaP_TCP.h"
#include "lib/iotaap/iotaap_adc/IoTaaP_ADC.h"
#include "lib/iotaap/iotaap_buzzer/IoTaaP_Buzzer.h"
#include "lib/iotaap/iotaap_hall/IoTaaP_Hall.h"
#include "lib/iotaap/iotaap_serial/IoTaaP_Serial.h"
#include "lib/iotaap/iotaap_dac/IoTaaP_DAC.h"
#include "lib/iotaap/iotaap_pwm/IoTaaP_PWM.h"
#include <Adafruit_I2CDevice.h>

class IoTaaP
{
public:
    IoTaaP();

    // IoTaaP libs
    IoTaaP_Misc misc;
    IoTaaP_OLED oled;
    IoTaaP_MQTT mqtt;
    IoTaaP_WiFi wifi;
    WiFiServer wifiServer;
    WiFiClient wifiClient;
    IoTaaP_TCP tcp;
    IoTaaP_ADC adc;
    IoTaaP_Buzzer buzzer;
    IoTaaP_Hall hall;
    IoTaaP_Serial serial;
    IoTaaP_DAC dac;
    IoTaaP_PWM pwm;

private:
};

#endif
