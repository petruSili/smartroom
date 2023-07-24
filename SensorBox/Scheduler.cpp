#include "Scheduler.h"
#include "Arduino.h"

volatile bool timerFlag;
hw_timer_t * timer = NULL; 
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED; //---- Variable used for mutual exclusion and used to avoid race conditions for the shared variable.

void IRAM_ATTR timerHandler(void){
  portENTER_CRITICAL_ISR(&timerMux);
  timerFlag = true;
  portEXIT_CRITICAL_ISR(&timerMux);
}

void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;    
  timer = timerBegin(0, 80, true);  //---------------------- The second parameter is a prescaler that indicates the frequency of the microcontroller, used to define the time.
  timerAttachInterrupt(timer, &timerHandler, true);
  startTimer(basePeriod);
  nTasks = 0;
}

bool Scheduler::addTask(Task* task){
  if (nTasks < MAX_TASKS-1){
    taskList[nTasks] = task;
    nTasks++;
    return true;
  } else {
    return false; 
  }
}
  
void Scheduler::schedule(){   
  if(timerFlag){   
    startTimer(basePeriod);
    for (int i = 0; i < nTasks; i++){
      if (taskList[i]->updateAndCheckTime(basePeriod)){
        taskList[i]->tick();
      }
    }
  }
}

void Scheduler::startTimer(int bPeriod){
  long period = 1000l*bPeriod;
  portENTER_CRITICAL(&timerMux);
  timerFlag = false;
  portEXIT_CRITICAL(&timerMux);
  timerAlarmWrite(timer, period, false);
  timerWrite(timer, 0);
  timerAlarmEnable(timer);
}
