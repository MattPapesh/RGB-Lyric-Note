#ifndef RGB_CommandBase_h
#define RGB_CommandBase_h

#include <Arduino.h>
#include "RGB_CommandReceiver.h"

class RGB_CommandBase
{
    private:

    String command_name = "";
    RGB_CommandReceiver* command_receiver_ptr = nullptr;
    
    bool is_scheduled = false;
    bool is_initialized = false;
    bool is_executing = false;
    bool is_finished = false;
    bool is_interrupted = false;

    void activelyUpdateScheduledState();

    public:

    void addRequirements(RGB_CommandReceiver* command_receiver_ptr, String command_name);  
    void run();
    
    void schedule();
    void cancel();

    bool isScheduled();
    bool isInitialized();
    bool isExecuting();
    bool isInterrupted();

    virtual void initialize();
    virtual void execute();
    virtual void end(bool interrupted);
    virtual bool isFinished();
};

#endif