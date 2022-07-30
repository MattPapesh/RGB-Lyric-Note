#include "RGB_CommandBase.h"

void RGB_CommandBase::activelyUpdateScheduledState()
{
    if(command_receiver_ptr->getCommandNameReceived() == command_name && !is_scheduled)
    {
        schedule();
    }
    else if(command_receiver_ptr->getCommandNameReceived() != command_name && is_scheduled)
    {
        cancel();
    }
}

void RGB_CommandBase::run()
{
    activelyUpdateScheduledState();

    if(is_scheduled && !is_interrupted && !is_finished && !is_initialized && !is_executing)
    {
        is_initialized = true;
        initialize();
    }
    else if(is_scheduled && !is_interrupted && !is_finished && is_initialized && !is_executing)
    {
        is_executing = true;
        execute();
        is_finished = isFinished();
    } 
    else if(is_interrupted || is_finished)
    {
        end(is_interrupted);

        is_scheduled = false;
        is_initialized = false;
        is_executing = false;
        is_finished = false;
        is_interrupted = false; 
    }
}

void RGB_CommandBase::addRequirements(RGB_CommandReceiver* command_receiver_ptr, String command_name)
{
    this->command_receiver_ptr = command_receiver_ptr;
    this->command_name = command_name;
}
    
void RGB_CommandBase::schedule()
{
    is_scheduled = true;
    
    is_initialized = false;
    is_executing = false;
    is_finished = false;
    is_interrupted = false; 
}

void RGB_CommandBase::cancel()
{
    is_interrupted = true;
}

bool RGB_CommandBase::isScheduled()
{
    return is_scheduled;
}

bool RGB_CommandBase::isInitialized()
{
    return is_initialized;
}

bool RGB_CommandBase::isExecuting()
{
    return is_executing;
}

bool RGB_CommandBase::isInterrupted()
{
    return is_interrupted;
}

void RGB_CommandBase::initialize() {}
void RGB_CommandBase::execute() {}
void RGB_CommandBase::end(bool interrupted) {}
bool RGB_CommandBase::isFinished() { return false; }