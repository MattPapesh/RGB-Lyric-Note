#ifndef RainbowCommand_h
#define RainbowCommand_h

#include <Arduino.h>
#include "../RGB_CommandBase.h"
#include "../RGB_CommandReceiver.h"

class RainbowCommand : public RGB_CommandBase
{
    private:

    public:

    RainbowCommand(RGB_CommandReceiver* command_receiver_ptr, String command_name);

    void initialize() override;
    void execute() override;
    void end(bool interrupted) override;
    bool isFinished() override;
};

#endif