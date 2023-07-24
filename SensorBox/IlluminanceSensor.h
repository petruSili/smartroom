#ifndef __ILLUMINANCESENSOR__
#define __ILLUMINANCESENSOR__

#include "Adafruit_TSL2591.h"

class IlluminanceSensor {
	
public: 
  IlluminanceSensor(): tsl(2591){};  
  void startSensor();
	float getIlluminance();
private:
  Adafruit_TSL2591 tsl;
};

#endif
