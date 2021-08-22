#ifndef LOGIC_H
#define LOGIC_H

#include "Arduino.h"

class Timer;

class Logic
{
public:

  enum State
  {
    HEATING,
    CRUISE,
    OFF,
  };
  
	Logic();

	void on_OnPressed();

	void on_TimerTimeout();

	void on_OffPressed();

	void stop();

	void run();

	void loop();
	
	void setTargetTemperature(unsigned int temp);

	State state() const;

  static bool isSaunaActive();

private:

	State _currentState;
	unsigned int _targetTemperature;
	Timer* _timer;
};

#endif
