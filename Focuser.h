
#ifndef Focuser_h
#define Focuser_h

#define DEGREES_PER_STEP 1.8

#include <inttypes.h>
#include <avr/io.h>
#include "AFMotor.h"

class Focuser
{
  public:
    Focuser(void);
    void move(int val);
    void stepSize(int val);
    void interpretCommand(char* command);
  private:
};

#endif
