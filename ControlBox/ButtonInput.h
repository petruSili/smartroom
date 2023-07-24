#ifndef __BUTTON_INPUT__
#define __BUTTON_INPUT__

#include "Input.h"
#include "Arduino.h"
class ButtonInput: public Input {
 
public: 
  ButtonInput(int pin, int* deviceList);
  int selectedDevice;
  virtual bool isReleased();
  virtual void notifyInterrupt(int pin);
  
private:
  int pin;
  int devicePos;
  int nextDevice;
  long lastEventTime;
  int* deviceList;
  
};

#endif
