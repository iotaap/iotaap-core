/*
 * IoTaaP - Internet of Things as a Platform
 * Connectivity platform for rapid development
 * 
 * MVT Solutions <iotaap@mvt-solutions.com>
 * https://www.mvt-solutions.com
 * https://iotaap.mvt-solutions.com
 * 
 * Copyright (c) 2017-2019 MVT Solutions
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice must be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __IOTAAP_H__
#define __IOTAAP_H__

// IoTaaP libs includes
#include "lib/iotaap/iotaap_misc/IoTaaP_Misc.h"
#ifdef ENABLE_ADC
#include "lib/iotaap/iotaap_adc/IoTaaP_ADC.h"
#endif
#ifdef ENABLE_ACCELEROMETER
#include "lib/iotaap/iotaap_accelerometer/IoTaaP_Accelerometer.h"
#endif
#ifdef ENABLE_OLED
#include "lib/iotaap/iotaap_oled/IoTaaP_OLED.h"
#endif
#ifdef ENABLE_BUZZER
#include "lib/iotaap/iotaap_buzzer/IoTaaP_Buzzer.h"
#endif
#ifdef ENABLE_HALL
#include "lib/iotaap/iotaap_hall/IoTaaP_Hall.h"
#endif
#ifdef ENABLE_SERIAL
#include "lib/iotaap/iotaap_serial/IoTaaP_Serial.h"
#endif
#ifdef ENABLE_WIFI
#include "lib/iotaap/iotaap_wifi/IoTaaP_WiFi.h"
#endif
#ifdef ENABLE_MQTT
#include "lib/iotaap/iotaap_mqtt/IoTaaP_MQTT.h"
#endif
#ifdef ENABLE_TCP
#include "lib/iotaap/iotaap_tcp/IoTaaP_TCP.h"
#endif
#ifdef ENABLE_DAC
#include "lib/iotaap/iotaap_dac/IoTaaP_DAC.h"
#endif
#ifdef ENABLE_PWM
#include "lib/iotaap/iotaap_pwm/IoTaaP_PWM.h"
#endif
#ifdef ENABLE_KAI
#include "lib/iotaap/iotaap_kai/IoTaaP_Kai.h"
#endif

// 3rd party libs includes
#ifdef ENABLE_DEBOUNCE
#include "lib/3rd_party/Debounce/Debounce.h"
#endif
#ifdef ENABLE_BTSERIAL
#include "BluetoothSerial.h"
#endif
#ifdef ENABLE_JSON
#include "lib/3rd_party/ArduinoJson/ArduinoJson-v6.12.0.h"
#endif

class IoTaaP
{
public:
    IoTaaP();

    // IoTaaP libs
    IoTaaP_Misc misc;
    #ifdef ENABLE_ADC
    IoTaaP_ADC adc;
    #endif
    #ifdef ENABLE_ACCELEROMETER
    IoTaaP_Accelerometer accelerometer;
    #endif
    #ifdef ENABLE_OLED
    IoTaaP_OLED oled;
    #endif
    #ifdef ENABLE_BUZZER
    IoTaaP_Buzzer buzzer;
    #endif
    #ifdef ENABLE_HALL
    IoTaaP_Hall hall;
    #endif
    #ifdef ENABLE_SERIAL
    IoTaaP_Serial serial;
    #endif
    #ifdef ENABLE_WIFI
    IoTaaP_WiFi wifi;
    #endif
    #ifdef ENABLE_MQTT
    IoTaaP_MQTT mqtt;
    #endif
    #ifdef ENABLE_TCP
    IoTaaP_TCP tcp;
    #endif
    #ifdef ENABLE_DAC
    IoTaaP_DAC dac;
    #endif
    #ifdef ENABLE_PWM
    IoTaaP_PWM pwm;
    #endif
    #ifdef ENABLE_KAI
    IoTaaP_Kai kai;
    #endif

    // 3rd party libs
    #ifdef ENABLE_BTSERIAL
    BluetoothSerial btSerial;
    #endif
    #ifdef ENABLE_TCPSERVER
    WiFiServer wifiServer;
    #endif
    #ifdef ENABLE_TCPCLIENT
    WiFiClient wifiClient;
    #endif

private:
};

#endif