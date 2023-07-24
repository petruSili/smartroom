#include "SmartRoomAsyncFSM.h"
#include "Configuration.h"
#include "MqttDeviceImpl.h"

SmartRoomAsyncFSM::SmartRoomAsyncFSM(TouchInput* pad, Device* device, LedRing* ledRing){ 
  this->pad = pad;
  this->device = device;
  this->ledRing = ledRing;
  pad->registerObserver(this);
}

void SmartRoomAsyncFSM::handleEvent(Event* ev) {
  if(ev->getType() == SENSOR_TOUCHED_EVENT) { 
    if(pad->eventCreated && !pad->isReleased()){  //---- Checks if the associated pad is the one that created the event and if the pad has been since released. 
      pad->eventCreated = false;              
      portENTER_CRITICAL(&eventMux);
      eventConsumed = true; //-------------------------- Removes the event from the shared queue.
      portEXIT_CRITICAL(&eventMux);
      if (device->getState() == OFF){
        device->switchOn();
        ledRing->showDeviceOn(device->getId());
      } else if(device->getState() == ON){
        device->switchOff();
        ledRing->showDeviceOff(device->getId());
      }   
    }
  }
}
