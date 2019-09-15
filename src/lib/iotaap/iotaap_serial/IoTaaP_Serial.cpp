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
 * @brief Reads one line from UART
 * 
 * @return String Returns one line of data received on UART
 */
String IoTaaP_Serial::getLn()
{
    return Serial.readString();
}