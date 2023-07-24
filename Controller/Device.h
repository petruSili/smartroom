#ifndef __DEVICE__
#define __DEVICE__

class Device {
public:
  virtual int getState() = 0;
  virtual void setState(int) = 0;
  virtual void switchOn() = 0;
  virtual void switchOff() = 0;    
};

#endif
