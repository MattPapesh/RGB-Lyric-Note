#include "RGB_CommandReceiver.h"

void RGB_CommandReceiver::serialEvent()
{
    delay(SERIAL_EVENT_DELAY_MILLIS);
  
    if(Serial && Serial.available())
    {
        command_name = getSerialTransmission();
        num_of_parameters = getSerialTransmission().toInt();

        if(parameter_ptrs != nullptr)
        {
            delete[] parameter_ptrs;
        }

        parameter_ptrs = new int[num_of_parameters];

        for(int i = 0; i < num_of_parameters; i++)
        {
            *(parameter_ptrs + i) = getSerialTransmission().toInt();
        }

        Serial.print("command: "); Serial.println(command_name);
        for(int i = 0; i < num_of_parameters; i++)
        {
            Serial.print("parameter: "); Serial.println(*(parameter_ptrs + i));
        }
    }
}

String RGB_CommandReceiver::getSerialTransmission()
{
    String transmission = "";
    char character = getTransmittedChar();

    while(receivingCommandTransmission(character))
    {
        if(character != NULL && character != SEND_SERIAL_ID && character != SENT_SERIAL_ID)
        {
            transmission += character;
        }

        character = getTransmittedChar();
    }

    return transmission;
}

char RGB_CommandReceiver::getTransmittedChar()
{
    if(Serial.available())
    {
        return (char)Serial.read();
    }
}

bool RGB_CommandReceiver::receivingCommandTransmission(char byte_sent)
{
    if(byte_sent == SEND_SERIAL_ID)
    {
        receiving_command_transmission = !receiving_command_transmission;
    }

    return receiving_command_transmission;
}


String RGB_CommandReceiver::getCommandNameReceived()
{
    return command_name;
}

int RGB_CommandReceiver::getNumOfParametersReceived()
{
    return num_of_parameters;
}

int* RGB_CommandReceiver::getParameterPTRsReceived()
{
    return parameter_ptrs;
}

int RGB_CommandReceiver::getParameterReceived(int index)
{
    if(index >= 0 && index < num_of_parameters)
    {
        return *(parameter_ptrs + index);
    }

    return 0;
}