#include "RGB_Pin.h"

RGB_Pin::RGB_Pin(Adafruit_PWMServoDriver* pin_driver_ptr, int pin)
{
    this->pin_driver_ptr = pin_driver_ptr;
    this->pin = pin;

    if(pin_driver_ptr == nullptr)
    {
        pin_driver_ptr->setPWMFreq(PIN_PWM_FREQ);
        pinMode(pin, OUTPUT);
    }
}

Adafruit_PWMServoDriver* RGB_Pin::getPinDriverPTR()
{
    return pin_driver_ptr;
}

int RGB_Pin::getPin()
{
    return pin;
}

void RGB_Pin::setColorPercentage(float pct)
{
    color_pct = pct;
}

float RGB_Pin::getColorPercentage()
{
    return color_pct;
}

void RGB_Pin::update()
{
    if(pin_driver_ptr != nullptr)
    {
        pin_driver_ptr->setPWM(pin, 0, color_pct * MAX_DRIVER_DUTY_CYCLE); 
    }
    else
    {
        analogWrite(pin, color_pct * MAX_DUTY_CYCLE);
    }
}