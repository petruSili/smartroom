/*
 * Class implements a touch toggle button.
 */

#ifndef __TOUCH_INPUT__
#define __TOUCH_INPUT__

#include "Input.h"

class TouchInput: public Input {
 
public: 
  TouchInput(int pin);
  virtual bool isReleased();
  virtual void notifyInterrupt(int pin);
  bool eventCreated;
  
private:
  int pin;  
  long lastEventTime;
  
};

#endif
