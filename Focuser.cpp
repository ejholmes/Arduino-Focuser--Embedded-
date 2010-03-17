

//ADDED FOR COMPATIBILITY WITH WIRING
extern "C" {
  #include <stdlib.h>
}

#include "WProgram.h"
#include "Focuser.h"

AF_Stepper motor(360 / DEGREES_PER_STEP, 2);

uint8_t u_stepType = 0;

Focuser::Focuser(void)
{
  motor.setSpeed(10);
  u_stepType = 8;
}

void Focuser::interpretCommand(Messenger *message)
{
  message->readChar();
  char command = message->readChar();
  
  switch(command){
    case 'M':
      move(message->readInt());
      break;
    case 'S':
      stepSize(message->readInt());
      break;
    case 'R':
      motor.release();
      break;
    case 'T':
      stepType(message->readInt());
      break;
  }
}

void Focuser::move(int val)
{
  if (val > 0) {
    motor.step(val, FORWARD, u_stepType);
  }
  else if (val < 0) {
    motor.step(abs(val), BACKWARD, u_stepType);
  }
  motor.release();
  Serial.println("M DONE");
}

void Focuser::stepType(int type)
{
  u_stepType = type;
}

void Focuser::stepSize(int val)
{
  motor.setSpeed(val);
}
