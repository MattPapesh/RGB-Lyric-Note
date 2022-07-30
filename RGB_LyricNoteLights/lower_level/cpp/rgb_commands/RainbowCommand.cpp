#include "RainbowCommand.h"

RainbowCommand::RainbowCommand(RGB_CommandReceiver* command_receiver_ptr, String command_name)
{
    addRequirements(command_receiver_ptr, command_name);
}

void RainbowCommand::initialize()
{
    
}

void RainbowCommand::execute() 
{

}

void RainbowCommand::end(bool interrupted) 
{

}

bool RainbowCommand::isFinished() 
{
    return false;
}