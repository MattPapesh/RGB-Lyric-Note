#include "RGB_LyricNoteLights.h"

void RGB_LyricNoteLights::begin()
{
    Serial.begin(SERIAL_BAUD_RATE);
  
    RGB_DRIVER_1.begin();
    RGB_DRIVER_2.begin();
  
    pinMode(A3, OUTPUT);
    digitalWrite(A3, HIGH);
}

bool once = true;

void RGB_LyricNoteLights::run()
{
    // This method must be called from the scheduler!
    RGB_CommandScheduler::run();

    if(once)
    {
        rainbow_lights_command.schedule();
        once = false;
    }
}