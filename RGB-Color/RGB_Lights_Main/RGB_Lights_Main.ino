#include <RGB_LyricNoteLights.h>

RGB_LyricNoteLights lyric_note_lights = RGB_LyricNoteLights();

void setup() {
  // put your setup code here, to run once:
  lyric_note_lights.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  lyric_note_lights.run(); 
}

void serialEvent()
{
  lyric_note_lights.runCommandReceiver();
}
