// green yellow - black red

#include "Focuser.h"
#include <Arduino_NET.h>

Focuser focuser = Focuser();

void setup(){
  Arduino.begin(19200);
  Arduino.attach(messageComplete);
}

void messageComplete(byte command, int argc, char** argv) {
  focuser.interpretCommand(command, argc, argv);
}

void loop(){
  while(Arduino.available() > 0) Arduino.process();
}


