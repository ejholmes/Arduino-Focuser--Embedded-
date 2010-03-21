

//ADDED FOR COMPATIBILITY WITH WIRING
extern "C" {
  #include <stdlib.h>
}

#include "WProgram.h"
#include "Focuser.h"

AF_Stepper motor(360 / DEGREES_PER_STEP, 2); // Create our stepper motor. I have mine on port 2 of the motor shield.

uint8_t u_stepType = 0;
long position = 0;

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
      move(message->readLong());
      break;
    case 'R': // Release motor coils
      motor.release();
      break;
    case 'P':
      setPosition(message->readLong());
      break;
    case 'G':
      printPosition();
      break;
    case 'H':
      Serial.flush();
      break;
  }
}

void Focuser::setPosition(long newpos)
{
  position = newpos;
  printPosition();
}

void Focuser::printPosition()
{
  Serial.print("P ");
  Serial.println(position);
}

//
// Function for issuing moves
//
void Focuser::move(long val)
{
  long move = val - position; // calculate move
  
  if(abs(move) > FAST)
  {
    long fastSteps = getFaststeps(move);
    
    motor.setSpeed(FASTSPEED);
    singleStep(fastSteps);
    
    motor.setSpeed(SLOWSPEED);
    microStep(move - fastSteps);
  }
  else
  {
    microStep(move);
  }
  
  motor.release(); // Release the motors when done. This works well for me but might not for others
  Serial.print("P ");
  Serial.println(position);
}

long Focuser::getFaststeps(long val)
{
  if(val > 0)
  {
    if(val % MICROSTEPS == 0)
      return val-MICROSTEPS;
    while(val % MICROSTEPS != 0)
    {
      val--;
    }
    return val;
  }
  else if (val < 0)
  {
    if(abs(val) % MICROSTEPS == 0)
      return val+MICROSTEPS;
    while(abs(val) % MICROSTEPS != 0)
    {
      val++;
    }
    return val;
  }
}

void Focuser::singleStep(long val)
{
  if (val > 0) {
    while(val > 0)
    {
      if(Serial.available() > 0)
        break;
      motor.step(1, FORWARD, SINGLE);
      position+=MICROSTEPS;
      val-=MICROSTEPS;
    }
  }
  else if (val < 0) {
    while(val < 0)
    {
      if(Serial.available() > 0 || position == 0)
        break;
      motor.step(1, BACKWARD, SINGLE);
      position-=MICROSTEPS;
      val+=MICROSTEPS;
    }
  }  
}

void Focuser::microStep(long val)
{
  if (val > 0) { // If move is positive, move forward
    while(val--)
    {
      if(Serial.available() > 0)
        break;
      motor.step(1, FORWARD, MICROSTEP);
      position++;
    }
  }
  else if (val < 0) { // else if move is negative, move backward
    long counter = abs(val);
    while(counter--)
    {
      if(Serial.available() > 0 || position == 0)
        break;
      motor.step(1, BACKWARD, MICROSTEP);
      position--;
    }
  }  
}
