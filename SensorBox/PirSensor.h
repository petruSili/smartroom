#ifndef __PIRSENSOR__
#define __PIRSENSOR__

class PirSensor {
		
public: 
	PirSensor(int pin);
	bool isDetected();
	
private:
  int pin;
  
};
	


#endif
