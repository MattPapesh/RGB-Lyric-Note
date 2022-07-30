#ifndef RGB_CommandReceiver_h
#define RGB_CommandReceiver_h

#include <Arduino.h>
#include <Wire.h>

class RGB_CommandReceiver
{
    private:

    const int SERIAL_EVENT_DELAY_MILLIS = 100;

    // CONSTANTS FOR RECEIVING TRANSMITTED RGB COMMANDS VIA TTL SERIAL COMMUNICATION!
    // If the slave arduino is sent this value, it knows that the following data is the command
    const char SEND_SERIAL_ID = (char)58;
    // If the slave arduino is sent this value, it knows that the entire command has been sent
    const char SENT_SERIAL_ID = (char)59;

    String command_name = "";
    int num_of_parameters = 0;
    int* parameter_ptrs = nullptr;
    bool receiving_command_transmission = false;

    void serialEvent();
    String getSerialTransmission();
    char getTransmittedChar();
    bool receivingCommandTransmission(char byte_sent);

    public:

    String getCommandNameReceived();
    int getNumOfParametersReceived();
    int* getParameterPTRsReceived();
    int getParameterReceived(int index);
};

#endif