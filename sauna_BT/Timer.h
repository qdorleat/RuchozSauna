//
// Created by qdorleat on 03.04.22.
//
#ifndef SAUNA_BT_TIMER_H
#define SAUNA_BT_TIMER_H

#include <ctime>


class Timer
{
public:
	Timer() : _startTimeS(0), _started(false), _timeOutFunc(nullptr)
	{
	}

	void start(void (*callbackWhenTimeOutReached)(), int *time_left_s_out)
	{
		// timestamp at timer start
		_started = true;
		_startTimeS = time(nullptr);
		_timeOutFunc = callbackWhenTimeOutReached;
    time_left_s = time_left_s_out;
	}

	void loop()
	{
		if (_started)
		{
			// timestamp at loop event
			auto currentTimeS = time(nullptr);
			time_t durationS = currentTimeS - _startTimeS;
      *time_left_s = COUNTER_DURATION - durationS; 
			if(static_cast<int>(durationS) > COUNTER_DURATION) {
				stop();
			}
		}
	}
private:

	// time reached
	void stop()
	{
		_started = false;
		if (_timeOutFunc)
		{
			_timeOutFunc();
		}
	}

	// Function callback called when the timer is over
	void (*_timeOutFunc)();
	// Counter duration in seconds
  static const int COUNTER_DURATION = 2700; //seconds = 45 minutes /;
//  static const int COUNTER_DURATION = 60; // seconds /;
	// Time when timer starts
	time_t _startTimeS;
	// Say if
	bool _started;
  //pointer to the time left
  int* time_left_s = NULL;
};

#endif //SAUNA_BT_TIMER_H
