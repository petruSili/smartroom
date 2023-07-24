#include "HomePresenceTask.h"
#include "Configuration.h"
#include <Arduino.h>

HomePresenceTask::HomePresenceTask(){}
  
void HomePresenceTask::init(int period){
  Task::init(period);   
}
/*
* isHome is set to true everytime the controller receives a message from the BLEScanner, 
* this task must check how much time elapsed since the last detection and set the variable accordingly.
*/
void HomePresenceTask::tick(){
  if(millis() - lastTimeHome > IS_HOME_INTERVAL){ 
    isHome = false;
  }   
}
