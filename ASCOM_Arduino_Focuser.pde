#include "Focuser.h"
#include "Messenger.h"

#define MAXSIZE 30

Focuser focuser = Focuser();
Messenger message = Messenger();

char command[MAXSIZE];

void setup(){
  Serial.begin(9600);
  Serial.flush();
  
  message.attach(messageCompleted);
  
  focuser.stepSize(10);
  
}

void messageCompleted(){
  while(message.available()){
    message.copyString(command, MAXSIZE);
  }
  focuser.interpretCommand(command);
}

void loop(){
  while(Serial.available()) message.process(Serial.read());
}


