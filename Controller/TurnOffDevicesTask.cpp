#include "TurnOffDevicesTask.h"
#include "Configuration.h"

TurnOffDevicesTask::TurnOffDevicesTask(Device** allDevices){
  this->allDevices = allDevices;    
}
  
void TurnOffDevicesTask::init(int period){
  Task::init(period);   
}
  
void TurnOffDevicesTask::tick(){
  int i;
  for(i=0; i < NUM_DEVICES; i++){
    if(allDevices[i]->getState() == ON){
      allDevices[i]->switchOff();
    }
   
  }
}
