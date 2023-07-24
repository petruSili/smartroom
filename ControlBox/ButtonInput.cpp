#include "ButtonInput.h"
#include "Arduino.h"
#include "Configuration.h"
#include "Timer.h"



ButtonInput::ButtonInput(int pin, int* deviceList){
  this->pin = pin;
  this->deviceList = deviceList;
  pinMode(pin, INPUT_PULLUP);
  devicePos = 0;
  nextDevice = 0;  
  bindInterrupt(pin);
  lastEventTime = millis();
  selectedDevice = deviceList[devicePos];
} 
  
bool ButtonInput::isReleased(){
  return digitalRead(pin) == HIGH;  
}

void ButtonInput::notifyInterrupt(int pin){
  long curr = millis();
  if (curr - lastEventTime > DEBOUNCING_TIME){         /* Ignores multiple presses due to encoder switch bouncing */
        lastEventTime = curr;
        if (isReleased()){
          if(timeExpired){                             /* User has limited time to go through the list and keep index,  */
            selectedDevice = deviceList[0];            /* once the time is OVER the index is set to 0 */
            timeExpired = false;
            devicePos = 0;
          }else {                                   
            nextDevice = (devicePos + 1)% NUM_VARLEVL_DEV;      /*  Goes to the next index in the unidirectional circular list  */
            selectedDevice = deviceList[nextDevice];
            devicePos = nextDevice;
          }       
          Event* ev;
          ev = new selectDevice(this);
          this->generateEvent(ev);
        }     
  }
}
