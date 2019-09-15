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
#include "lib/3rd_party/AdafruitGFX/Adafruit_GFX.h"
#include "lib/3rd_party/AdafruitSSD1306/Adafruit_SSD1306.h"
#include "lib/3rd_party/Debounce/Debounce.h"
#include "WiFi.h"
#include "lib/3rd_party/PubSubClient/PubSubClient.h"
#ifdef BLUETOOTH_SERIAL_SUPPORT
#include "lib/3rd_party/BluetoothSerial/BluetoothSerial.h"
#endif

#include "lib/iotaap/IoTaaP_OLED/iotaap_splash.h"

#define ONBOARD_LED1 15
#define ONBOARD_LED2 2
#define ONBOARD_BUT1 0
#define ONBOARD_BUT2 25
#define BATSENS_PIN 36
#define ONBOARD_BUZZER 32
#define ADC_SAMPLES 1
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define ONBOARD_DEBOUNCE_TIME 20
#define WIFI_TIMEOUT 5000
#define MQTT_TIMEOUT 3000
#define ACCELEROMETER_X_PIN 33
#define ACCELEROMETER_Y_PIN 34
#define ACCELEROMETER_Z_PIN 35

/**
 * @brief Structure that contains WiFi connection status and IP address
 * 
 */
struct wifiConnectionInfo
{
    int status;
    IPAddress ipAddress;
};

/**
 * @brief Structure that contains accelerometer values
 * 
 */
struct accelerometer
{
    uint16_t x;
    uint16_t y;
    uint16_t z;
};

class IoTaaP
{
public:
    IoTaaP();

    void blinkOnboardLed(int LED, int interval = 100, int loops = 1);
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
    bool getBUT2();
    unsigned long getAnalogValue(int pin);
    void initSerial(unsigned long baud);
    void printlnSerial(String string);
    String getLnSerial();
    wifiConnectionInfo connectToWifi(const char *ssid, const char *pass);
    bool mqttConnect(const char *clientID, const char *server, uint16_t port, MQTT_CALLBACK_SIGNATURE, const char *user = '\0', const char *password = '\0');
    uint16_t mqttKeepAlive();
    bool mqttPublish(const char *topic, const char *payload);
    void mqttSubscribe(const char *topic);
    int scanWiFi();
    String getScannedWiFi(uint8_t i);
    IPAddress openWiFiAP(const char *ssid, const char *password = NULL);
    WiFiClient openTCPconnection(const char *host, uint16_t port);
    void sendTCP(const char *payload);
    String readTCPstring(const char delimiter);
    void closeTCP();
    int readHall();
    double getVoltage(int reading);
    double getBatteryPercentage();
    accelerometer getAccelerometerRaw();
    void sleep(int seconds = 1);
    void restart();
    void setDAC(uint8_t value);
    void setupPWM(uint8_t channel, double freq, uint8_t resolution, uint8_t pin);
    void setPWM(uint8_t channel, uint32_t duty);
    void displayBitmap(int16_t x, int16_t y, const uint8_t bitmap[], uint16_t color);

private:
    Adafruit_SSD1306 _display;
    Bounce _debouncer;
    WiFiClient _wifiClient;
    WiFiClient _tcpWifiClient;
    PubSubClient _mqttPubSub;
    bool _reconnectMQTT();
    const char *_mqttclientID;
    const char *_mqttuser;
    const char *_mqttpassword;
};

#endif