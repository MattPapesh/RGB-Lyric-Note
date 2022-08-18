#include <RGB_LyricNoteConsole.h>
#include <Wire.h>

RGB_LyricNoteConsole console = RGB_LyricNoteConsole();

void setup() {
  // put your setup code here, to run once:
  console.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  console.run();
}
