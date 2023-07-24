/* 
 *  Class sends the Esp32 in deep sleep for a period of time.
*/ 

#ifndef __POWER_SAVING__
#define __POWER_SAVING__

#include "Device.h"
#include "Connection.h"
#include "LedRing.h"

class PowerSaving { 
public:
  PowerSaving(Connection* connection, const char* presenceTopic);
  void sleepMode();     
private:  
  void askPresenceUpdate();
  long requestTime;
  Connection* connection;
  const char* presenceTopic;
};

#endif
