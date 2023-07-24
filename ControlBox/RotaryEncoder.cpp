#include "RotaryEncoder.h"
#include "Configuration.h"
#include "AiEsp32RotaryEncoder.h"


AiEsp32RotaryEncoder RotaryEncoder::rotaryEncoder = AiEsp32RotaryEncoder(ROT_ENC_PIN_CLK, ROT_ENC_PIN_DT, ROT_ENC_PIN_VCC, ROT_ENC_STEPS);
RotaryEncoder::RotaryEncoder(){}

void RotaryEncoder::init(){
  rotaryEncoder.begin();           
  rotaryEncoder.setBoundaries(MIN_LEVEL, MAX_LEVEL, false);
  rotaryEncoder.setAcceleration(50);
  rotaryEncoder.setup( [] {rotaryEncoder.readEncoder_ISR(); });
}

void RotaryEncoder::setValue(int value){
  rotaryEncoder.setEncoderValue(value);;
}

int RotaryEncoder::getValue(){
  return  (int)rotaryEncoder.readEncoder();
}
