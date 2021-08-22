#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include "Logic.h"

/*
 * Timer class
 * The timer class holds a timeOut functor. The timeOut functor is called at stop() function call
 * The timeOut functor is set when the timer is started  
 */
class Timer
{
  static const int COUNTER_DURATION = 5; // 30 /* MINUTES */ * 60 /* SECONDS */;
  time_t _startTimeS;

public:

  Timer(Logic* logic);

  void stop();
  
  void start();

  void loop();

  private:
  Logic* _logic;
};

#endif
