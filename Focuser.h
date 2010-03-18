
#ifndef Focuser_h
#define Focuser_h

#define DEGREES_PER_STEP 1.8

#include <inttypes.h>
#include <avr/io.h>
#include "AFMotor.h"
#include "Messenger.h"

class Focuser
{
  public:
    Focuser(void); // Constructor
    void move(int val); // Function for moving the focuser
    void stepSize(int val); // Function for changing the motor RPM
    void interpretCommand(Messenger *message); // Function for interpreting a command string
    void stepType(int type); // Function for changing the step type used during move()'s
  private:
    uint8_t u_stepType;
};

#endif
