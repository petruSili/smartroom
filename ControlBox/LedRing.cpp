#include "LedRing.h"
#include "Configuration.h"

/* Initializes the ledRing object and turns off all leds. */

void LedRing::init(){
  ledRing.begin();           
  ledRing.show();            
  ledRing.setBrightness(BRIGHTNESS);
  ledRing.clear();
}

/* Fades in then out 4 leds of colour red representing the switch off of a certain device. */

void LedRing::showDeviceOff(int deviceId){
  switch(deviceId){
    case 1:
      for(uint16_t i=16; i<20; i++){
         ledRing.setPixelColor(i, 255, 0, 0);
      }
      break;
    case 2:
       ledRing.setPixelColor(0, 255, 0, 0);
       ledRing.setPixelColor(1, 255, 0, 0);
       ledRing.setPixelColor(22, 255, 0, 0);
       ledRing.setPixelColor(23, 255, 0, 0);
      break;
    case 3:
      for(uint16_t i=4; i<8; i++){
         ledRing.setPixelColor(i, 255, 0, 0);
      }
      break;     
   } 
  fadeInFadeOut();
}

/* Fades in then out 4 leds of colour green representing the switch on of a certain device. */

void LedRing::showDeviceOn(int deviceId){
  switch(deviceId){
    case 1:
      for(uint16_t i=16; i<20; i++){
         ledRing.setPixelColor(i, 0, 255, 0);
      }
      break;
    case 2:
       ledRing.setPixelColor(0, 0, 255, 0);
       ledRing.setPixelColor(1, 0, 255, 0);
       ledRing.setPixelColor(22, 0, 255, 0);
       ledRing.setPixelColor(23, 0, 255, 0);
      break;
    case 3:
      for(uint16_t i=4; i<8; i++){
         ledRing.setPixelColor(i, 0, 255, 0);
      }
      break;    
   } 
  fadeInFadeOut();
}

/* Shows which device intensity you're about to change. */

void LedRing::showSelectedDevice(int deviceId){
  switch(deviceId){
    case 1:
      for(uint16_t i=0; i<24; i++){
         ledRing.setPixelColor(i, 0, 255, 196);
      }
      ledRing.setBrightness(BRIGHTNESS);
      ledRing.show();
      delay(5);
      break;
    case 2:
      for(uint16_t i=0; i<24; i++){
         ledRing.setPixelColor(i, 255, 0, 0);
      }
      ledRing.setBrightness(BRIGHTNESS);
      ledRing.show();
      delay(5);
      break;
    case 3:
      for(uint16_t i=0; i<24; i++){
         ledRing.setPixelColor(i, 255, 0, 196);
      }
      ledRing.setBrightness(BRIGHTNESS);
      ledRing.show();
      delay(5);
      break;
  }
}
  
void LedRing::fadeInFadeOut(){
  uint8_t i = 1;
  for(i=1; i<BRIGHTNESS; i*=2){
    ledRing.setBrightness(i);
    ledRing.show();
    delay(20);
  }
  for(i=BRIGHTNESS; i>1; i/=2){
    ledRing.setBrightness(i);
    ledRing.show();
    delay(20);
  }
  ledRing.clear();
  ledRing.show();
}

/* Shows the intensity of the device (following a green-yellow-orange-red colour scheme) as you change it.
   The intensity go from 0 to 10, 0 is represented with 4 white leds.  */

void LedRing::showIntensity(uint16_t intensity){
  uint16_t i;
  uint16_t level = intensity/10; 
  ledRing.clear();
  if(intensity == 0){                                       
       ledRing.setPixelColor(0, 127, 127, 127);
       ledRing.setPixelColor(1, 127, 127, 127);
       ledRing.setPixelColor(22, 127, 127, 127);
       ledRing.setPixelColor(23, 127, 127, 127);
   }
   else{
    for(i=0; i<=level; i++){
      switch (i){
        case 0:
          ledRing.setPixelColor(21, 0, 255, 0);
          ledRing.setPixelColor(20, 0, 255, 0);
          break;
        case 1:
          ledRing.setPixelColor(19, 100, 255, 0);
          ledRing.setPixelColor(18, 100, 255, 0);
          break;
        case 2:
          ledRing.setPixelColor(17, 200, 255, 0);
          ledRing.setPixelColor(16, 200, 255, 0);
          break;       
        case 3:
          ledRing.setPixelColor(15, 255, 255, 0);
          ledRing.setPixelColor(14, 255, 255, 0);
          break;        
        case 4:
          ledRing.setPixelColor(13, 255, 200, 0);
          ledRing.setPixelColor(12, 255, 200, 0);
          break;      
        case 5:
          ledRing.setPixelColor(11, 255, 150, 0);
          ledRing.setPixelColor(10, 255, 150, 0);
          break;       
        case 6:
          ledRing.setPixelColor(9, 255, 100, 0);
          ledRing.setPixelColor(8, 255, 100, 0);
          break;
        case 7:
          ledRing.setPixelColor(7, 255, 50, 0);
          ledRing.setPixelColor(6, 255, 50, 0);
          break;          
        case 8:
          ledRing.setPixelColor(5, 255, 0, 0);
          ledRing.setPixelColor(4, 255, 0, 0);
          break;                  
        case 9:
          ledRing.setPixelColor(3, 255, 0, 0);
          ledRing.setPixelColor(2, 255, 0, 0);
          break;
      }           
    }
  }
  ledRing.show();
  delay(5);
}

void LedRing::turnOff(){
  ledRing.clear();
  ledRing.show();
}
