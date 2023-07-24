#include "CoolingTask.h"
#include "Configuration.h"

CoolingTask::CoolingTask(DeviceExt* device){
  this->device = device;    
}
  
void CoolingTask::init(int period){
  Task::init(period); 
}
  
void CoolingTask::tick(){
  switch (roomCoolingState){
    case COOL:
      if(device->getState() == ON){
        device->switchOff();
      }
      break;
    case WARM:
      if(device->getIntensity() < WARM_SPEED){
        device->changeIntensity(WARM_SPEED);
      }
      break;
    case HOT:
      if(device->getIntensity() < HOT_SPEED){
        device->changeIntensity(HOT_SPEED);
      }
      break;
    case VERY_HOT:
      if(device->getIntensity() < VERY_HOT_SPEED){
        device->changeIntensity(VERY_HOT_SPEED);
      }
      break;
  }
}
