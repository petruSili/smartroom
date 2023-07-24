#ifndef __DEVICE_EXT__
#define __DEVICE_EXT__

#include "Device.h"

class DeviceExt : public Device {
public:
  virtual int getIntensity() = 0;
  virtual void setIntensity(int) = 0;
  virtual void changeIntensity(int) = 0;  
};

#endif
