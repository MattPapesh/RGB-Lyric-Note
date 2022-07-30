#include "RGB_Cavity.h"

void RGB_Cavity::setPinColorPercentage(RGB_Pin* pin_ptr, float pct)
{
    if(pin_ptr != nullptr)
    {
        pin_ptr->setColorPercentage(pct);
    }
}

void RGB_Cavity::updatePin(RGB_Pin* pin_ptr)
{
    if(pin_ptr != nullptr)
    {
        pin_ptr->update();
    }
}

RGB_Cavity::RGB_Cavity(RGB_Pin* blue_pin_ptr, RGB_Pin* green_pin_ptr, RGB_Pin* red_pin_ptr)
{
    this->red_pin_ptr = red_pin_ptr;
    this->green_pin_ptr = green_pin_ptr;
    this->blue_pin_ptr = blue_pin_ptr;
}

void RGB_Cavity::setRGBPercentages(float red_pct, float green_pct, float blue_pct)
{
    setPinColorPercentage(red_pin_ptr, red_pct);
    setPinColorPercentage(green_pin_ptr, green_pct);
    setPinColorPercentage(blue_pin_ptr, blue_pct);
}

float RGB_Cavity::getRedPercentage()
{
    if(red_pin_ptr != nullptr)
    {
        return red_pin_ptr->getColorPercentage();
    }

    return 0;
}

float RGB_Cavity::getGreenPercentage()
{
    if(green_pin_ptr != nullptr)
    {
        return green_pin_ptr->getColorPercentage();
    }

    return 0;
}

float RGB_Cavity::getBluePercentage()
{
    if(blue_pin_ptr != nullptr)
    {
        return blue_pin_ptr->getColorPercentage();
    }

    return 0;
}

void RGB_Cavity::update()
{
    updatePin(red_pin_ptr);
    updatePin(green_pin_ptr);
    updatePin(blue_pin_ptr);
}