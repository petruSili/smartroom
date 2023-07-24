#ifndef __TIMER__
#define __TIMER__


class Timer {
    
public:  
  Timer(int period);    /* period in ms */
  void init();  
  void startTimer();
private:
  int period;
};


#endif
