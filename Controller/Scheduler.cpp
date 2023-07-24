#include "Scheduler.h"
#include <TimerOne.h>
#include "Configuration.h"

volatile bool timerFlag;

void timerHandler(void){
  timerFlag = true;
  //Serial.println(F("T"));
}

void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  timerFlag = false;
  long period = 1000l*basePeriod;
  Timer1.initialize(period);
  Timer1.attachInterrupt(timerHandler);
  homeTasks = 0;
  awayTasks = 0;
  inRoomTasks = 0;
  notInRoomTasks = 0;
  asleepTasks = 0;
  awakeTasks = 0;
}

void Scheduler::addHomeTask(Task* task){
  if (homeTasks < MAX_TASKS-1){
    homeTaskList[homeTasks] = task;
    homeTasks++;
  } else {
    Serial.println(F("Warning: addHomeTask buffer exceeded!")); 
  }
}
void Scheduler::addAwayTask(Task* task){
  if (awayTasks < MAX_TASKS-1){
    awayTaskList[awayTasks] = task;
    awayTasks++;
  } else {
    Serial.println(F("Warning: addHomeTask buffer exceeded!"));  
  }
}
void Scheduler::addInRoomTask(Task* task){
  if (inRoomTasks < MAX_TASKS-1){
    inRoomTaskList[inRoomTasks] = task;
    inRoomTasks++;
  } else {
    Serial.println(F("Warning: addInRoomTask buffer exceeded!")); 
  }
}
void Scheduler::addNotInRoomTask(Task* task){
  if (notInRoomTasks < MAX_TASKS-1){
    notInRoomTaskList[notInRoomTasks] = task;
    notInRoomTasks++;
  } else {
    Serial.println(F("Warning: addNotInRoomTask buffer exceeded!")); 
  }
}
void Scheduler::addAsleepTask(Task* task){
  if (asleepTasks < MAX_TASKS-1){
    asleepTaskList[asleepTasks] = task;
    asleepTasks++;
  } else {
    Serial.println(F("Warning: addAsleepTask buffer exceeded!")); 
  }
}
void Scheduler::addAwakeTask(Task* task){
  if (awakeTasks < MAX_TASKS-1){
    awakeTaskList[awakeTasks] = task;
    awakeTasks++;
  } else {    
    Serial.println(F("Warning: addAwakeTask buffer exceeded!")); 
  }
}
/*
 * The scheduler is provided with a list of tasks for every state of the system, and executes that list acoording to the logic flow.
 * For example: if the user is AWAY, the scheduler will not consider tasks regarding the user being at HOME. 
 * The logic flow of the scheduler:
 * 
 *      |->Home -|---->InRoom-------|---->Asleep
 *      |        |                  |
 * -----|        |---->NotInRoom    |---->Awake
 *      |
 *      |->Away      
 */

 
void Scheduler::schedule(){    
  if(timerFlag){
    timerFlag = false;
    if(isHome){
      for (int i = 0; i < homeTasks; i++){
        if (homeTaskList[i]->updateAndCheckTime(basePeriod)){
          homeTaskList[i]->tick();
        }
      }
      if(isInRoom){
        for (int i = 0; i < inRoomTasks; i++){
          if (inRoomTaskList[i]->updateAndCheckTime(basePeriod)){
            inRoomTaskList[i]->tick();
          }
        }
        if(isAsleep){
          for (int i = 0; i < asleepTasks; i++){
            if (asleepTaskList[i]->updateAndCheckTime(basePeriod)){
              asleepTaskList[i]->tick();
            }
          }
        }else{
          for (int i = 0; i < awakeTasks; i++){
            if (awakeTaskList[i]->updateAndCheckTime(basePeriod)){
              awakeTaskList[i]->tick();
            }
          }
        }
      }else{
       for (int i = 0; i < notInRoomTasks; i++){
          if (notInRoomTaskList[i]->updateAndCheckTime(basePeriod)){
            notInRoomTaskList[i]->tick();
          }
        } 
      }
        
    }else{
      for (int i = 0; i < awayTasks; i++){
        if (awayTaskList[i]->updateAndCheckTime(basePeriod)){
          awayTaskList[i]->tick();
        }
      }
    }
  }
}
