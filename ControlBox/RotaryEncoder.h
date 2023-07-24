#ifndef __ROTARY_ENCODER__
#define __ROTARY_ENCODER__

#include "AiEsp32RotaryEncoder.h"
#include "Configuration.h"

class RotaryEncoder { 
  
public:

  RotaryEncoder();
  void init();
  int getValue(); 
  void setValue(int value);
private:
 static  AiEsp32RotaryEncoder rotaryEncoder;
  
};
#endif
