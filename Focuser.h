
#ifndef Focuser_h
#define Focuser_h

#define DEGREES_PER_STEP 1.8

#define FASTSPEED 100
#define SLOWSPEED 10

#define FAST 100 // Move fast if move is more than 100
#define SLOWSTEPS 10 // Perform last 10 steps slowly

#include <inttypes.h>
#include <avr/io.h>
#include "AFMotor.h"
#include "Messenger.h"

class Focuser
{
  public:
    Focuser(void); // Constructor
    void move(long val); // Function for moving the focuser
    void interpretCommand(Messenger *message); // Function for interpreting a command string
    void setPosition(long newpos); // For setting position
    void reverse(bool rev); // For setting motor polarity
  private:
    void printPosition(); // Prints current position to serial
    void singleStep(long val); // Step using SINGLE. However, since we define 1 step as a microstep, a SINGLE step is 32 microstes as defined in AFMotor.h
    void microStep(long val); // Microstep
    long getFaststeps(long val); // Returns the number of steps we can do as single steps. Returns a factor of 32.
    uint8_t u_stepType;
    long position;
    bool reversed;
    bool finish;
};

#endif
