#include "TouchInput.h"
#include "Arduino.h"
#include "Configuration.h"

TouchInput::TouchInput(int pin){
  this->pin = pin;
  pinMode(pin, INPUT); 
  bindInterrupt(pin);
  lastEventTime = millis();  
  eventCreated = false;
} 
  
bool TouchInput::isReleased(){
 return touchRead(pin) < TOUCH_THRESHOLD;  
}

void TouchInput::notifyInterrupt(int pin){
  long curr = millis();
  if (curr - lastEventTime > DEBOUNCING_TIME){
    if (!eventCreated && isReleased()){ //--------- The touch sensor connot create an event unless the last one it created has been consumed or the pad hasn't been released.
        lastEventTime = curr;
        eventCreated = true;
        Event* ev;
        ev = new SensorTouched(this);
        this->generateEvent(ev);
    }
  }
}
