#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

#define MAX_TASKS 50

class Scheduler {
  
  int basePeriod;
  int nTasks;
  Task* taskList[MAX_TASKS];  
  void startTimer(int bPeriod);

public:
  void init(int basePeriod);  
  virtual bool addTask(Task* task);  
  virtual void schedule();
};

#endif
