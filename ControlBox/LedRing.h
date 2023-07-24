/*
 * Class that manages the LEDs for the visual feedback.
 */

#ifndef __LED_RING__
#define __LED_RING__
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include "Configuration.h"

class LedRing { 
  
public:

  LedRing(uint8_t dataPin): ledRing(NUM_PIXELS, dataPin, NEO_GRB + NEO_KHZ800){pinMode(dataPin, OUTPUT);};
  void init();
  void showDeviceOn(int deviceId);
  void showDeviceOff(int deviceId); 
  void showSelectedDevice(int deviceId);
  void showIntensity(uint16_t intensity);
  void turnOff();
private:
  void fadeInFadeOut();
  Adafruit_NeoPixel ledRing;
  
};
#endif
