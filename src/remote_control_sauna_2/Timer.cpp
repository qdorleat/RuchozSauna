#include <ctime>

#include "Timer.h"
#include "Logic.h"
#include "Arduino.h"

Timer::Timer(Logic* logic)
  : _logic (logic)
{
}

void Timer::stop()
{
  if(_logic)
  {
    _logic->on_TimerTimeout();
  }    
}

void Timer::start() 
{
  _startTimeS = time(nullptr);
}

void Timer::loop() {
  auto currentTimeS = time(nullptr);
  time_t durationS = currentTimeS - _startTimeS;
  Serial.print("time: ");
  Serial.print(durationS);
  Serial.print(" time2go: ");
  Serial.println(COUNTER_DURATION-durationS);

  if(static_cast<int>(durationS) > COUNTER_DURATION) {
    stop();
  }
}
