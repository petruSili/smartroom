#include "AwakeIlluminanceTask.h"
#include "Configuration.h"

AwakeIlluminanceTask::AwakeIlluminanceTask(Device* nightLamps){
  this->nightLamps = nightLamps;    
}
  
void AwakeIlluminanceTask::init(int period){
  Task::init(period);   
}
/*  
 *   This task manages the lights according to the illuminance when the user is in the room. 
 */
void AwakeIlluminanceTask::tick(){
  switch (roomIlluminanceState){
    case DARK:
      if(nightLamps->getState() == OFF){
        nightLamps->switchOn();
      }
      break;
    case BRIGHT:
      if(nightLamps->getState() == ON){
        nightLamps->switchOff();
      }
      break;
  }
}
