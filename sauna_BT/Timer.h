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

	void start(void (*callbackWhenTimeOutReached)())
	{
		// timestamp at timer start
		_started = true;
		_startTimeS = time(nullptr);
		_timeOutFunc = callbackWhenTimeOutReached;
	}

	void loop()
	{
		if (_started)
		{
			// timestamp at loop event
			auto currentTimeS = time(nullptr);
			time_t durationS = currentTimeS - _startTimeS;

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
	static const int COUNTER_DURATION = 5; // 30 /* MINUTES */ * 120 /* SECONDS */;
	// Time when timer starts
	time_t _startTimeS;
	// Say if
	bool _started;
};

#endif //SAUNA_BT_TIMER_H
