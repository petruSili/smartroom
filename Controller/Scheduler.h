#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

#define MAX_TASKS 5

class Scheduler {
  
  int basePeriod;
  int homeTasks;
  int awayTasks;
  int inRoomTasks;
  int notInRoomTasks;
  int asleepTasks;
  int awakeTasks;
  Task* homeTaskList[MAX_TASKS];  
  Task* awayTaskList[MAX_TASKS];
  Task* inRoomTaskList[MAX_TASKS];
  Task* notInRoomTaskList[MAX_TASKS];
  Task* asleepTaskList[MAX_TASKS];
  Task* awakeTaskList[MAX_TASKS]; 
public:
  void init(int basePeriod);  
  void addHomeTask(Task* task);
  void addAwayTask(Task* task);
  void addInRoomTask(Task* task);
  void addNotInRoomTask(Task* task);
  void addAsleepTask(Task* task);
  void addAwakeTask(Task* task);    
  void schedule();
};

#endif
