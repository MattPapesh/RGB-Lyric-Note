#include "RGB_CommandScheduler.h"

RGB_CommandBase** RGB_CommandScheduler::command_ptr_ptrs = nullptr;
int RGB_CommandScheduler::num_of_commands = 0;
int RGB_CommandScheduler::current_instance_index = 0;

static void RGB_CommandScheduler::registerRGBCommand(RGB_CommandBase* command_ptr)
{
    RGB_CommandBase** temp_command_ptr_ptrs = new RGB_CommandBase*[num_of_commands + 1]; 

    for(int i = 0; i < num_of_commands && command_ptr_ptrs != nullptr; i++)
    {
        *(temp_command_ptr_ptrs + i) = *(command_ptr_ptrs + i);
    }

    *(temp_command_ptr_ptrs + num_of_commands) = command_ptr;

    delete[] command_ptr_ptrs;
    command_ptr_ptrs = temp_command_ptr_ptrs;
    num_of_commands++;
}

static RGB_CommandBase* RGB_CommandScheduler::getInstance()
{
    RGB_CommandBase* instance = nullptr;

    // Given that num_of_commands is incremented for every command pointer registered, 
    // a command pointer instance indexed at a value less than this variable should never by a nullpointer unless
    // a nullpointer command pointer is registered.
    if(current_instance_index >= 0 && current_instance_index < num_of_commands)
    {
        instance = *(command_ptr_ptrs + current_instance_index);
        current_instance_index++;
    }
    else if(num_of_commands > 0)
    {
        instance = *command_ptr_ptrs;
        current_instance_index = 0;
    }
    else
    {
        current_instance_index = 0;
    }

    return instance;
}

static void RGB_CommandScheduler::run()
{
    RGB_CommandBase* command_ptr = getInstance();

    if(command_ptr != nullptr)
    {
        command_ptr->run();
    }
}