#ifndef __INPUT__
#define __INPUT__

#include "async_fsm.h"
#include "Configuration.h"

class Input : public EventSource {
public: 
  virtual bool isReleased() = 0;
};

class SensorTouched: public Event {
public:
  SensorTouched(Input* source) : Event(SENSOR_TOUCHED_EVENT){
    this->source = source;  
  } 
 
  Input* getSource(){
    return source;
  } 
private:
  Input* source;  
};

class selectDevice: public Event {
public:
  selectDevice(Input* source) : Event(CHANGE_LEVEL_EVENT){
    this->source = source;  
  } 
 
  Input* getSource(){
    return source;
  } 
private:
  Input* source;  
};

#endif
