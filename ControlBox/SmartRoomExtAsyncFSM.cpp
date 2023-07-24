#include "SmartRoomExtAsyncFSM.h"
#include "Configuration.h"
#include "ButtonInput.h"
#include "Timer.h"
#include "RotaryEncoder.h"
#include "MqttDeviceExtImpl.h"
#include "LedRing.h"

SmartRoomExtAsyncFSM::SmartRoomExtAsyncFSM(TouchInput* pad, DeviceExt* device, ButtonInput* deviceSelector, Timer* timer, LedRing* ledRing, RotaryEncoder* rotaryEncoder){ 
  this->pad = pad;
  this->timer = timer;
  this->device = device;
  this->ledRing = ledRing;
  this->rotaryEncoder = rotaryEncoder;
  this->deviceSelector = deviceSelector; 
  pad->registerObserver(this);
  deviceSelector->registerObserver(this);
}

void SmartRoomExtAsyncFSM::handleEvent(Event* ev) {
  switch (ev->getType()) {
    case SENSOR_TOUCHED_EVENT: 
      if(pad->eventCreated && !pad->isReleased()){  //------- Checks if the associated pad is the one that created the event and if the pad has been since released.
        pad->eventCreated = false;              
        portENTER_CRITICAL(&eventMux);
        eventConsumed = true; 
        portEXIT_CRITICAL(&eventMux);
        if (device->getState() == OFF){         
          device->switchOn();
          ledRing->showDeviceOn(device->getId());
        } else if(device->getState() == ON){
          device->switchOff();
          ledRing->showDeviceOff(device->getId());
        }  
      }    
      break;
    case CHANGE_LEVEL_EVENT:
      if(deviceSelector->selectedDevice == device->getId()){ 
        portENTER_CRITICAL(&eventMux);
        eventConsumed = true; 
        portEXIT_CRITICAL(&eventMux);
        timer->startTimer();  //------------------------------ User has "TIMER_PERIOD" time to either change intensity or select another device.
        ledRing->showSelectedDevice(device->getId());
        rotaryEncoder->setValue(device->getIntensity());
        while(!timeExpired && deviceSelector->selectedDevice == device->getId()){ //----- Waits in the loop until the time expires or a different device has been selected.
          if(rotaryEncoder->getValue() != device->getIntensity()){
            ledRing->showIntensity(rotaryEncoder->getValue()); 
            device->setIntensity(rotaryEncoder->getValue());                 
            timer->startTimer(); //--------------------------- On every action the timer is restarted.   
          }
        }
        device->changeIntensity(rotaryEncoder->getValue());
        ledRing->turnOff();
      }
      break; 
  }
}
