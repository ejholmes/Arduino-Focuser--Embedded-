// green yellow - black red

#include "Focuser.h"
#include "Messenger.h"

Focuser focuser = Focuser();
Messenger message = Messenger();

void setup(){
  Serial.begin(9600);
  Serial.flush();
  
  message.attach(messageCompleted);
  
  focuser.stepSize(10);
  
}

void messageCompleted(){
  focuser.interpretCommand(&message);
}

void loop(){
  while(Serial.available()) message.process(Serial.read());
}


