#include "IoTaaP_Serial.h"

/**
 * @brief Construct a new IoTaaP_Serial::IoTaaP_Serial object
 * 
 */
IoTaaP_Serial::IoTaaP_Serial()
{
}

/**
 * @brief Initializes UART port with specified baud
 * 
 * @param baud Valid baud rate
 */
void IoTaaP_Serial::init(unsigned long baud)
{
    Serial.begin(baud);
}

/**
 * @brief Prints one line string to UART
 * 
 * @param string Text to be printed
 */
void IoTaaP_Serial::printLn(String string)
{
    Serial.println(string);
}

/**
 * @brief Reads data from UART. This function is non-blocking and it will break if delimiter is not received within 1000mS after the last character.
 * 
 * @return String Returns data received on UART
 */
String IoTaaP_Serial::getString()
{
    return Serial.readString();
}

/**
 * @brief Reads data from UART until delimiter char received. This function is non-blocking and it will break if delimiter is not received within 1000mS after the last character.
 * 
 * @param delimiter Termination character
 * @return String Returns data received on UART
 */
String IoTaaP_Serial::getStringUntil(char delimiter)
{
    return Serial.readStringUntil(delimiter);
}

/**
 * @brief Checks if data is available on serial port
 * 
 * @return int Returns value different than 0 if true
 */
int IoTaaP_Serial::isAvailable()
{
    return Serial.available();
}

/**
 * @brief Reads one character from UART buffer
 * 
 * @return int Character read
 */
int IoTaaP_Serial::readChar()
{
    return Serial.read();
}

/**
 * @brief Writes one character to the UART
 * 
 * @param ch Character to be written
 * @return size_t Number of written characters
 */
size_t IoTaaP_Serial::writeChar(char ch)
{
    return Serial.write(ch);
}