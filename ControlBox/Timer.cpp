#include "Arduino.h"
#include "Timer.h"
#include "Configuration.h"

hw_timer_t * timeR = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED; //--- The variable serves to guarantee the mutual exclusion over the timeOver variable.
  
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  timeExpired = true;
  portEXIT_CRITICAL_ISR(&timerMux);
}

Timer::Timer(int period){
  this->period = period;
}

void Timer::init(){
  timeR = timerBegin(0, 80, true);  //---------------------- The second parameter is a prescaler that indicates the frequency of the microcontroller, used to define the time.
  timerAttachInterrupt(timeR, &onTimer, true);
}

void Timer::startTimer(){
  portENTER_CRITICAL(&timerMux);
  timeExpired = false;
  portEXIT_CRITICAL(&timerMux);
  timerAlarmWrite(timeR, period * 1000, false);
  timerWrite(timeR, 0);
  timerAlarmEnable(timeR);
}
