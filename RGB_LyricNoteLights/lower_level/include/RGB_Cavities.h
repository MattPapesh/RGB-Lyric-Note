#ifndef RGB_Cavities_h
#define RGB_Cavities_h

#include <Arduino.h>
#include "RGB_Cavity.h"

class RGB_Cavities 
{
    private:

    RGB_Cavity** cavity_ptr_ptrs = nullptr;
    int num_of_cavities = 0;

    public:

    RGB_Cavities(RGB_Cavity* cavity_ptrs[], int num_of_cavities);
    ~RGB_Cavities();

    void interfaceCavity(int cavity_index, float pct_red, float pct_green, float pct_blue);
    void interfaceAllCavities(float pct_red, float pct_green, float pct_blue);
    void update();   
};

#endif