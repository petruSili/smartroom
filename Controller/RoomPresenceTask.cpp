#include "RoomPresenceTask.h"
#include "Configuration.h"
#include <Arduino.h>

RoomPresenceTask::RoomPresenceTask(){}
  
void RoomPresenceTask::init(int period){
  Task::init(period);   
}

/*
 * isInRoom is set to true everytime the controller receives a message from the PIR, 
 * this task must check how much time elapsed since the last detection and set the variable accordingly.
 */
void RoomPresenceTask::tick(){
  if(millis() - lastTimeInRoom > IS_INROOM_INTERVAL){ 
    isInRoom = false;
  }    
}
