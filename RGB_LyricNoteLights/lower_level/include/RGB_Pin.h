#ifndef RGB_Pin_h
#define RGB_Pin_h

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

class RGB_Pin
{
    private:
  
    const int PIN_PWM_FREQ = 200;
    const int MAX_DUTY_CYCLE = 30;
    const int MAX_DRIVER_DUTY_CYCLE = 4095;
    
    Adafruit_PWMServoDriver* pin_driver_ptr = nullptr;
    int color_pct = 0;
    int pin = 0;

    public:

    RGB_Pin(Adafruit_PWMServoDriver* pin_driver_ptr, int pin);
    
    Adafruit_PWMServoDriver* getPinDriverPTR();
    int getPin();
    void setColorPercentage(float pct);
    float getColorPercentage();
    void update();
};

#endif