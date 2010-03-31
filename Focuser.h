
#ifndef Focuser_h
#define Focuser_h

#define DEGREES_PER_STEP 1.8

#define FASTSPEED 100
#define SLOWSPEED 10

#define FAST 100 // Move fast if move is more than 100
#define SLOWSTEPS 10 // Perform last 10 steps slowly

#define MOVE            'M'
#define HALT            'H'
#define POSITION        'P'
#define REVERSE         'R'
#define PRINT_POSITION  'G'
#define RELEASE         'L'

#include <inttypes.h>
#include <avr/io.h>
#include "AFMotor.h"

class Focuser
{
  public:
    Focuser(void); // Constructor
    void move(long val); // Function for moving the focuser
    void interpretCommand(int command, int argc, char** argv); // Function for interpreting a command string
    void setPosition(long newpos); // For setting position
    void reverse(bool rev); // For setting motor polarity
  private:
    void printPosition(); // Prints current position to serial
    void step(long val, uint8_t steptype);
    long position;
    bool reversed;
};

#endif
