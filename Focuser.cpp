

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

void Focuser::interpretCommand(char* command)
{
  switch(command[0]){
    case 'F': //Move forwad
      move((int)command[1]);
      break;
    case 'B': //Move backward
      move((int)command[1]);
      break;
  }
}

void Focuser::move(int val)
{
  if (val > 0) {
    motor.step(val, FORWARD, MICROSTEP);
  }
  else if (val < 0) {
    motor.step(val, BACKWARD, MICROSTEP);
  }
}

void Focuser::stepSize(int val)
{
  motor.setSpeed(val);
}
