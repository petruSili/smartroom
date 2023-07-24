/*
 * A asynchronus FSM that manages the events of a simple ON/OFF device.
 */


#ifndef __SMART_ROOM_ASYNC_FSM__
#define __SMART_ROOM_ASYNC_FSM__

#include "LedRing.h"
#include "async_fsm.h"
#include "TouchInput.h"
#include "MqttDeviceImpl.h"

class SmartRoomAsyncFSM : public AsyncFSM{
  
public:
  SmartRoomAsyncFSM(TouchInput* pad, Device* device, LedRing* ledRing);
  void handleEvent(Event* ev);
private:
  TouchInput* pad;
  Device* device;
  LedRing* ledRing;
};   

#endif
