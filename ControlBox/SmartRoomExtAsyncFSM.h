/*
 * An asynchronous FSM that manages the events of a device with ON/OFF and Intensity controls.
 */
 
#ifndef __SMART_ROOM_EXT_ASYNC_FSM__
#define __SMART_ROOM_EXT_ASYNC_FSM__

#include "Timer.h"
#include "LedRing.h"
#include "async_fsm.h"
#include "TouchInput.h"
#include "ButtonInput.h"
#include "MqttDeviceExtImpl.h"
#include "RotaryEncoder.h"


class SmartRoomExtAsyncFSM : public AsyncFSM {
  
public:
  SmartRoomExtAsyncFSM(TouchInput* pad, DeviceExt* device, ButtonInput* deviceSelector, Timer* timer, LedRing* ledRing, RotaryEncoder* rotaryEncoder);
  void handleEvent(Event* ev);
private:
  TouchInput* pad;
  DeviceExt* device;
  ButtonInput* deviceSelector;
  RotaryEncoder* rotaryEncoder;
  Timer* timer;
  LedRing* ledRing;
};   

#endif
