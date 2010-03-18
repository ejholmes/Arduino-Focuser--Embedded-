

//ADDED FOR COMPATIBILITY WITH WIRING
extern "C" {
  #include <stdlib.h>
}

#include "WProgram.h"
#include "Focuser.h"

AF_Stepper motor(360 / DEGREES_PER_STEP, 2); // Create our stepper motor. I have mine on port 2 of the motor shield.

uint8_t u_stepType = 0;

//
// Constructor
// 
Focuser::Focuser(void)
{
  motor.setSpeed(10); // Set a default RPM of 10
  u_stepType = 8; // Set step type to microstepping.
}

//
// Function for interpreting a command string of the format ": COMMAND <ARGUMENT> #"
//
void Focuser::interpretCommand(Messenger *message)
{
  message->readChar(); // Reads ":"
  char command = message->readChar(); // Read the command
  
  switch(command){
    case 'M': // Move
      move(message->readInt());
      break;
    case 'S': // Set RPM
      stepSize(message->readInt());
      break;
    case 'R': // Release motor coils
      motor.release();
      break;
    case 'T': // Set step type to be used in move()'s
      stepType(message->readInt());
      break;
  }
}

//
// Function for issuing moves
//
void Focuser::move(int val)
{
  if (val > 0) { // If val is positive, move forward
    motor.step(val, FORWARD, u_stepType);
  }
  else if (val < 0) { // else if val is negative, move backward
    motor.step(abs(val), BACKWARD, u_stepType); // We take the absolute value of val since motor.step requires an unsigned int
  }
  motor.release(); // Release the motors when done. This works well for me but might not for others
  Serial.println("M DONE"); // Tell the client that we are done moving.
}

//
// Function for changing to step type
// Possible values are 1 = SINGLE, 2 = DOUBLE, 3 = INTERLEAVE, 8 = MICROSTEP (These are defined in AFMotor.h)
// 
void Focuser::stepType(int type)
{
  u_stepType = type;
}

//
// Function for changing the motor's RPM
// A higher value makes the motor run faster. A good starting point is 10.
//
void Focuser::stepSize(int val)
{
  motor.setSpeed(val);
}
