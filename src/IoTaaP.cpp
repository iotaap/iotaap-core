#include "IoTaaP.h"

/**
 * @brief Construct a new IoTaaP:: IoTaaP object
 * 
 */
IoTaaP::IoTaaP() : _display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1)
{
    analogSetSamples(ADC_SAMPLES);
    this->makePinOutput(ONBOARD_LED);
    this->makePinInput(ONBOARD_BUT1);
}

/**
 * @brief Blinks onboard LED for given interval and repeats loop 
 * 
 * @param interval Time in ms between LED states
 * @param loops Number of loops to repeat
 */
void IoTaaP::blinkOnboardLed(int interval, int loops)
{
    for (int i = 0; i < loops; i++)
    {
        this->setPin(ONBOARD_LED);
        delay(interval);
        this->clearPin(ONBOARD_LED);
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
 * @return true if not pressed
 * @return false if pressed
 */
bool IoTaaP::getBUT1()
{
    return digitalRead(ONBOARD_BUT1);
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
 * @brief Keep the connection with MQTT alive, and recconect if lost
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
 * @brief Publis payload to the specified topic
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