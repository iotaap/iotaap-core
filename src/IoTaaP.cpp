#include "IoTaaP.h"

/**
 * @brief Construct a new IoTaaP:: IoTaaP object
 * 
 */
IoTaaP::IoTaaP() : _display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1)
{
    analogSetSamples(ADC_SAMPLES);
    this->makePinOutput(ONBOARD_LED1);
    this->makePinOutput(ONBOARD_LED2);
    this->makePinInput(ONBOARD_BUT1);
    this->makePinInput(ONBOARD_BUT2);
}

/**
 * @brief Blinks onboard LED for given interval and repeats loop 
 * 
 * @param LED Onboard LED, can be ONBOARD_LED1 or ONBOARD_LED2
 * @param interval Time in ms between LED states
 * @param loops Number of loops to repeat
 */
void IoTaaP::blinkOnboardLed(int LED, int interval, int loops)
{
    for (int i = 0; i < loops; i++)
    {
        this->setPin(LED);
        delay(interval);
        this->clearPin(LED);
        delay(interval);
    }
}

/**
 * @brief Defines pin as OUTPUT, must be called before setting pin state
 * 
 * @param pin Pin to be defined as input
 */
void IoTaaP::makePinOutput(int pin)
{
    pinMode(pin, OUTPUT);
}

/**
 * @brief Defines pin as INPUT, must be called before reading pin state
 * 
 * @param pin Pin to be defined as input
 */
void IoTaaP::makePinInput(int pin)
{
    if (pin != ONBOARD_BUT1)
    {
        pinMode(pin, INPUT);
    }
    else
    {
        pinMode(pin, INPUT_PULLUP);
    }
}

/**
 * @brief Sets the pin (HIGH state)
 * 
 * @param pin Pin to set
 */
void IoTaaP::setPin(int pin)
{
    digitalWrite(pin, HIGH);
}

/**
 * @brief Clears the pin (LOW state)
 * 
 * @param pin Pin to be cleared 
 */
void IoTaaP::clearPin(int pin)
{
    digitalWrite(pin, LOW);
}

/**
 * @brief Initializes integrated OLED
 * 
 */
void IoTaaP::initOLED()
{
    this->_display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    this->_display.clearDisplay();
    this->_display.display();
}

/**
 * @brief Shows text on integrated OLED. OLED must be initialized first
 * 
 * @param text Text to be printed
 * @param x Text location on x coordinate
 * @param y Text location on y coordinate
 */
void IoTaaP::showTextOLED(const String text, int x, int y)
{
    this->_display.clearDisplay();
    this->_display.setTextSize(1);
    this->_display.setTextColor(WHITE);
    this->_display.setCursor(x, y);
    this->_display.println(text);
    this->_display.display();
}

/**
 * @brief Initializes onboard buzzer, must be called before buzzer is used
 * 
 */
void IoTaaP::initBuzzer()
{
    ledcSetup(0, 127, 8);
    ledcAttachPin(ONBOARD_BUZZER, 0);
}

/**
 * @brief Generates tone on the buzzer
 * 
 * @param freq Tone frequency
 * @param forever If TRUE, tone will be reporduced until buzzerStop() is called
 * @param durationMs Tone duration, will be ignored if 'forever' is true
 */
void IoTaaP::buzzerTone(int freq, bool forever, int durationMs)
{
    ledcWriteTone(0, freq);
    if (!forever)
    {
        delay(durationMs);
        this->buzzerStop();
    }
}

/**
 * @brief Stops and detaches onboard buzzer. Buzzer must be initialized first.
 * 
 */
void IoTaaP::buzzerStop()
{
    ledcDetachPin(ONBOARD_BUZZER);
    pinMode(ONBOARD_BUZZER, OUTPUT);
    digitalWrite(ONBOARD_BUZZER, LOW);
}

/**
 * @brief Reads state of Button1 
 * 
 * @return true if pressed
 * @return false if not pressed
 */
bool IoTaaP::getBUT1()
{
    return !digitalRead(ONBOARD_BUT1);
}

/**
 * @brief Reads state of Button2 
 * 
 * @return true if pressed
 * @return false if not pressed
 */
bool IoTaaP::getBUT2()
{
    return !digitalRead(ONBOARD_BUT2);
}

/**
 * @brief Reads analog value from analog pin
 * 
 * @param pin Andalog pin to read value from
 * @return unsigned long 12bit analog value
 */
unsigned long IoTaaP::getAnalogValue(int pin)
{
    return analogRead(pin);
}

/**
 * @brief Initializes UART port with specified baud
 * 
 * @param baud Valid baud rate
 */
void IoTaaP::initSerial(unsigned long baud)
{
    Serial.begin(baud);
}

/**
 * @brief Prints one line string to UART
 * 
 * @param string Text to be printed
 */
void IoTaaP::printlnSerial(String string)
{
    Serial.println(string);
}

/**
 * @brief Reads one line from UART
 * 
 * @return String Returns one line of data received on UART
 */
String IoTaaP::getLnSerial()
{
    return Serial.readString();
}

/**
 * @brief Connects to the WiFi AP
 * 
 * @param ssid AP SSID
 * @param pass AP Password
 * @return wifiConnectionInfo Returns structure containing status 1 and IP address if connected successfully, or status -1 and IP 0.0.0.0 if there was a problem
 */
wifiConnectionInfo IoTaaP::connectToWifi(const char *ssid, const char *pass)
{
    wifiConnectionInfo connectionInfo;
    int timeoutCounter = 0;
    WiFi.mode(WIFI_STA);
    WiFi.setHostname("localhost");
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        timeoutCounter = (timeoutCounter + 1) / 2;
        if (timeoutCounter >= WIFI_TIMEOUT)
        {
            connectionInfo.status = -1;
            connectionInfo.ipAddress = IPAddress(0, 0, 0, 0);
            return connectionInfo;
        }
    }

    connectionInfo.status = 1;
    connectionInfo.ipAddress = WiFi.localIP();

    return connectionInfo;
}

/**
 * @brief Connects to the MQTT server on a desired port
 * 
 * @param clientID Client ID that will be used in communication
 * @param server MQTT server IP address or URL
 * @param port MQTT port of the server
 * @param user Optional MQTT instance username
 * @param password Optional MQTT instance password 
 * @return true if successfully connected
 * @return false if there was a problem
 */
bool IoTaaP::mqttConnect(const char *clientID, const char *server, uint16_t port, MQTT_CALLBACK_SIGNATURE, const char *user, const char *password)
{
    this->_mqttclientID = clientID;
    this->_mqttuser = user;
    this->_mqttpassword = password;

    this->_mqttPubSub = PubSubClient(this->_wifiClient);

    this->_mqttPubSub.setServer(server, port);
    this->_mqttPubSub.setCallback(callback);

    if (!this->_mqttPubSub.connected())
    {
        return this->_reconnectMQTT();
    }
    return true;
}

/**
 * @brief Reconnect to MQTT server 
 * 
 * @return true if succesfully connected
 * @return false it there was a problem
 */
bool IoTaaP::_reconnectMQTT()
{
    int timeoutCounter = 0;

    // Loop until we're reconnected
    while (!this->_mqttPubSub.connected())
    {
        // Attempt to connect
        if (this->_mqttuser == '\0')
        {
            if (this->_mqttPubSub.connect(this->_mqttclientID))
            {
                return true;
            }
        }
        else
        {
            if (this->_mqttPubSub.connect(this->_mqttclientID, this->_mqttuser, this->_mqttpassword))
            {
                return true;
            }
        }

        delay(500);
        timeoutCounter = (timeoutCounter + 1) / 2;
        if (timeoutCounter >= MQTT_TIMEOUT)
        {
            return false;
        }
        timeoutCounter++;
    }
    return true;
}

/**
 * @brief Keep the connection with MQTT alive, and reconnect if lost. Should be put in the main loop
 * 
 * @return uint16_t Returns 2 if succesfully reconnected, returns 0 if there was a problem and returns 1 if already connected
 */
uint16_t IoTaaP::mqttKeepAlive()
{
    if (!this->_mqttPubSub.connected())
    {
        if (this->_reconnectMQTT())
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }
    this->_mqttPubSub.loop();
    return 1;
}

/**
 * @brief Publish payload to the specified topic
 * 
 * @param topic MQTT topic
 * @param payload MQTT topic payload
 * @return true if successfully connected
 * @return false if there was a problem
 */
bool IoTaaP::mqttPublish(const char *topic, const char *payload)
{
    return this->_mqttPubSub.publish(topic, payload);
}

/**
 * @brief Subscribe to the MQTT topic
 * 
 * @param topic Topic name
 */
void IoTaaP::mqttSubscribe(const char *topic)
{
    this->_mqttPubSub.subscribe(topic);
}

/**
 * @brief Scans for open WiFi networks and returns number of networks discovered
 * 
 * @return int Number of networks discovered
 */
int IoTaaP::scanWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    return WiFi.scanNetworks();
}

/**
 * @brief Returns SSID of discovered network
 * 
 * @param i Specify from which network item want to get the information
 * @return String SSID string of the specified item on the networks scanned list
 */
String IoTaaP::getScannedWiFi(uint8_t i)
{
    return WiFi.SSID(i);
}

/**
 * @brief Opens WiFi access point with provided credentials. If password is not provided AP will be open
 * 
 * @param ssid AP SSID
 * @param password AP Password (optional)
 * @return IPAddress Returns local IP address if successfully opened or empty IPAddress if not
 */
IPAddress IoTaaP::openWiFiAP(const char *ssid, const char *password)
{

    if (password == NULL)
    {
        if (WiFi.softAP(ssid))
        {
            return WiFi.softAPIP();
        }
    }
    else
    {
        if (WiFi.softAP(ssid, password))
        {
            return WiFi.softAPIP();
        }
    }

    return IPAddress();
}

/**
 * @brief Opens TCP connection on given host and port
 * 
 * @param host Host IP or DNS
 * @param port Host port
 * @return WiFiClient Returns configured WiFiClient object or empty object if there was a problem
 */
WiFiClient IoTaaP::openTCPconnection(const char *host, uint16_t port)
{

    if (!this->_tcpWifiClient.connect(host, port))
    {
        return WiFiClient();
    }
    return this->_tcpWifiClient;
}

/**
 * @brief Sends payload to opened TCP connection
 * 
 * @param payload Payload to be sent
 */
void IoTaaP::sendTCP(const char *payload)
{
    this->_tcpWifiClient.print(payload);
}

/**
 * @brief Reads string from TCP until delimiter is received
 * 
 * @param delimiter Delimiter character
 * @return String Returns received payload
 */
String IoTaaP::readTCPstring(const char delimiter)
{
    return this->_tcpWifiClient.readStringUntil(delimiter);
}

/**
 * @brief Closes opened TCP connection
 * 
 */
void IoTaaP::closeTCP()
{
    this->_tcpWifiClient.stop();
}

/**
 * @brief Reads onboard hall sensor value
 * 
 * @return int Value for HALL sensor (without LNA)
 */
int IoTaaP::readHall()
{
    return hallRead();
}

/**
 * @brief Returns voltage (V) from A/D reading
 * 
 * @param reading RAW A/D reading (0-4095);
 * @return double Calculated calibrated voltage
 */
double IoTaaP::getVoltage(int reading)
{
    if (reading < 1 || reading > 4095)
        return 0;
    return (-0.000000000000016 * pow(reading, 4) + 0.000000000118171 * pow(reading, 3) - 0.000000301211691 * pow(reading, 2) + 0.001109019271794 * reading + 0.034143524634089);
}

/**
 * @brief Returns current battery percentage
 * 
 * @return double Battery percentage
 */
double IoTaaP::getBatteryPercentage()
{
    return round(((this->getVoltage(this->getAnalogValue(BATSENS_PIN)) * 2) / 4.2) * 100);
}

/**
 * @brief Returns RAW (0-4095) values of accelerometer x,y,z axes
 * 
 * @return accelerometer Structure with x,y,z values
 */
accelerometer IoTaaP::getAccelerometerRaw()
{
    accelerometer acc;

    acc.x = this->getAnalogValue(ACCELEROMETER_X_PIN);
    acc.y = this->getAnalogValue(ACCELEROMETER_Y_PIN);
    acc.z = this->getAnalogValue(ACCELEROMETER_Z_PIN);

    return acc;
}

/**
 * @brief Deep sleep with timer Wake Up after defined time in seconds (default 1);
 * 
 * @param seconds Time in seconds
 */
void IoTaaP::sleep(int seconds)
{
    esp_sleep_enable_timer_wakeup(seconds * 1000000);
    esp_deep_sleep_start();
}

/**
 * @brief Restarts IoTaaP
 * 
 */
void IoTaaP::restart()
{
    esp_restart();
}

/**
 * @brief Sets onboard DAC output
 * 
 * @param value DAC value (0-255)
 */
void IoTaaP::setDAC(uint8_t value)
{
    dacWrite(DAC2, value);
}

/**
 * @brief Setups the PWM channel, and attaches pin
 * 
 * @param channel PWM channel (1-15)
 * @param freq PWM Frequency
 * @param resolution PWM resolution (1-16)
 * @param pin PWM pin
 */
void IoTaaP::setupPWM(uint8_t channel, double freq, uint8_t resolution, uint8_t pin)
{
    ledcSetup(channel, freq, resolution);
    ledcAttachPin(pin, channel);
}

/**
 * @brief Sets PWM duty cycle to PWM channel. setupPWM() must be called before
 * 
 * @param channel Preset PWM channel
 * @param duty PWM duty cycle
 */
void IoTaaP::setPWM(uint8_t channel, uint32_t duty)
{
    ledcWrite(channel, duty);
}

/**
 * @brief Displays bitmap on OLED. initOLED() must be called before
 * 
 * @param x Start X coordinate (usually 0)
 * @param y Start Y coordinate (Usually 0)
 * @param bitmap Bitmap to show
 * @param color Bitmap color (usually 1)
 */
void IoTaaP::displayBitmap(int16_t x, int16_t y, const uint8_t bitmap[], uint16_t color)
{
    this->_display.drawBitmap(x, y, bitmap, SCREEN_WIDTH, SCREEN_HEIGHT, color);
    this->_display.display();
}