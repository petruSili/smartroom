#include "AsleepIlluminanceTask.h"
#include "Configuration.h"
#include <Arduino.h>

AsleepIlluminanceTask::AsleepIlluminanceTask(Device* nightLamps){
  this->nightLamps = nightLamps;    
}
  
void AsleepIlluminanceTask::init(int period){
  Task::init(period); 
  timerStart = 0; 
}

/*  Turns the nightLamps ON if: the room is DARK, the nightLamps are OFF and motion has been detected in the last 2 seconds.
 *  Turns the nightLamps OFF if: the nightLamps are ON and the room is BRIGHT or the time since the last detected motion has exceeded NIGHT_LIGHT_TIME.
 *  The task keeps track of the time when motion is detected to prolong the timer accordingly. 
 */
 
void AsleepIlluminanceTask::tick(){
  switch (roomIlluminanceState){
  case DARK: 
    if(millis() - lastDetectedMotion < 2000){
      timerStart = millis();
        if(nightLamps->getState() == OFF){
          nightLamps->switchOn();
        }       
    }else if(millis() - timerStart > NIGHT_LIGHT_TIME){
      if(nightLamps->getState() == ON){
        nightLamps->switchOff();
      }
    }       
  break;
  case BRIGHT:
    if(nightLamps->getState() == ON){
      nightLamps->switchOff();
    }
  break;
  }
}
