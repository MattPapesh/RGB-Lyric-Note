#ifndef RGB_CommandScheduler_h
#define RGB_CommandScheduler_h

#include <Arduino.h>
#include "RGB_CommandBase.h"

class RGB_CommandScheduler
{
    private:

    static RGB_CommandBase** command_ptr_ptrs;
    static int num_of_commands;
    static int current_instance_index;

    static RGB_CommandBase* getInstance();

    public:

    static void registerRGBCommand(RGB_CommandBase* command_ptr);
    static void run();
};

#endif