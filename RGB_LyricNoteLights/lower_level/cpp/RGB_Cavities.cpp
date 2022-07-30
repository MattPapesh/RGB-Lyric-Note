#include "RGB_Cavities.h"

RGB_Cavities::RGB_Cavities(RGB_Cavity* cavity_ptrs[], int num_of_cavities)
{
    this->cavity_ptr_ptrs = new RGB_Cavity*[num_of_cavities];
    this->num_of_cavities = num_of_cavities;

    for (int i = 0; i < num_of_cavities; i++)
    {
        *(this->cavity_ptr_ptrs + i) = cavity_ptrs[i];
    }
}

void RGB_Cavities::interfaceCavity(int cavity_index, float red_pct, float green_pct, float blue_pct)
{
    if(cavity_index >= 0 && cavity_index < num_of_cavities && cavity_ptr_ptrs != nullptr && *(cavity_ptr_ptrs + cavity_index) != nullptr)
    {
        (*(cavity_ptr_ptrs + cavity_index))->setRGBPercentages(red_pct, green_pct, blue_pct);
    }
}

void RGB_Cavities::interfaceAllCavities(float red_pct, float green_pct, float blue_pct)
{
    for (int i = 0; i < num_of_cavities; i++)
    {
        interfaceCavity(i, red_pct, green_pct, blue_pct);
    }
}

void RGB_Cavities::update()
{
    for (int i = 0; i < num_of_cavities; i++)
    {
        (*(cavity_ptr_ptrs + i))->update();
    }
}