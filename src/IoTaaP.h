/*
 * IoTaaP - Internet of Things as a Platform
 * Connectivity platform that even a child can understand
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
 * The above copyright notice and this permission notice shall be included in
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



#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "lib/Debounce/Debounce.h"
#include "WiFi.h"
#include "lib/MQTT/PubSubClient.h"

#define ONBOARD_LED 2
#define ONBOARD_BUT1 0
#define ONBOARD_BUZZER 14
#define ADC_SAMPLES 1
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define ONBOARD_DEBOUNCE_TIME 20
#define WIFI_TIMEOUT 5000
#define MQTT_TIMEOUT 3000

/**
 * @brief Structure that contains WiFi connection status and IP address
 * 
 */
struct wifiConnectionInfo
{
    int status;
    IPAddress ipAddress;
};

class IoTaaP
{
public:
    IoTaaP();

    void blinkOnboardLed(int interval = 100, int loops = 1);
    void makePinOutput(int pin);
    void makePinInput(int pin);
    void setPin(int pin);
    void clearPin(int pin);
    void initOLED();
    void showTextOLED(String text, int x = 0, int y = 0);
    void initBuzzer();
    void buzzerTone(int freq = 1000, bool forever = false, int durationMs = 500);
    void buzzerStop();
    bool getBUT1();
    unsigned long getAnalogValue(int pin);
    void initSerial(unsigned long baud);
    void printlnSerial(String string);
    String getLnSerial();
    wifiConnectionInfo connectToWifi(const char *ssid, const char *pass);
    bool mqttConnect(const char *clientID, const char *server, uint16_t port, MQTT_CALLBACK_SIGNATURE, const char *user = '\0', const char *password = '\0');
    uint16_t mqttKeepAlive();
    bool mqttPublish(const char *topic, const char *payload);
    void mqttSubscribe(const char *topic);

private:
    Adafruit_SSD1306 _display;
    Bounce _debouncer;
    WiFiClient _wifiClient;
    PubSubClient _mqttPubSub;
    bool _reconnectMQTT();
    const char *_mqttclientID;
    const char *_mqttuser;
    const char *_mqttpassword;
};

#endif