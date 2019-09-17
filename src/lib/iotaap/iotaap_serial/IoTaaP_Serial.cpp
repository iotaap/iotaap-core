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