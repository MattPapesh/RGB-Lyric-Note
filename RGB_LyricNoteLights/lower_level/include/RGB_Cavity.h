#ifndef RGB_Cavity_h
#define RGB_Cavity_h

#include <Arduino.h>
#include "RGB_Pin.h"

class RGB_Cavity
{
    private:

    RGB_Pin* red_pin_ptr = nullptr;
    RGB_Pin* green_pin_ptr = nullptr;
    RGB_Pin* blue_pin_ptr = nullptr;

    void setPinColorPercentage(RGB_Pin* pin_ptr, float pct);
    void updatePin(RGB_Pin* pin_ptr);

    public:

    RGB_Cavity(RGB_Pin* blue_pin_ptr, RGB_Pin* green_pin_ptr, RGB_Pin* red_pin_ptr);
    
    void setRGBPercentages(float red_pct, float green_pct, float blue_pct);
    float getRedPercentage();
    float getGreenPercentage();
    float getBluePercentage();
    void update();
};

#endif