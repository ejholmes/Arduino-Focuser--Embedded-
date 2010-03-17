

//ADDED FOR COMPATIBILITY WITH WIRING
extern "C" {
  #include <stdlib.h>
}

#include "WProgram.h"
#include "Focuser.h"

AF_Stepper motor(360 / DEGREES_PER_STEP, 2);

Focuser::Focuser(void)
{
  motor.setSpeed(10);
}

void Focuser::interpretCommand(Messenger *message)
{
  message->readChar();
  char command = message->readChar();
  
  switch(command){
    case 'F':
      move(message->readInt());
      break;
    case 'B':
      move((message->readInt() * -1));
      break;
    case 'S':
      stepSize(message->readInt());
      break;
  }
}

void Focuser::move(int val)
{
  if (val > 0) {
    motor.step(val, FORWARD, MICROSTEP);
  }
  else if (val < 0) {
    motor.step(abs(val), BACKWARD, MICROSTEP);
  }
  Serial.println("DONE");
}

void Focuser::stepSize(int val)
{
  motor.setSpeed(val);
}
