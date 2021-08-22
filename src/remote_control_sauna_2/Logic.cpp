#include "Logic.h"
#include "Timer.h"
#include "Arduino.h"

static int saunaGate = 26;      // output pin for the sauna main current

bool Logic::isSaunaActive()
{
  return !digitalRead(saunaGate);
}

Logic::Logic() : 
	_targetTemperature(0.0),
	_currentState(OFF)
{
  _timer = new Timer(this);
}

void Logic::on_OnPressed()
{
	_currentState = HEATING;
	_timer->start();
	digitalWrite(saunaGate, LOW);
}

void Logic::on_TimerTimeout()
{
	stop();
}

void Logic::on_OffPressed()
{
	stop();
}

void Logic::stop()
{
	_timer->stop();
	_currentState = OFF;
	digitalWrite(saunaGate, HIGH);
}

void Logic::run()
{
	pinMode(saunaGate, OUTPUT);
	stop();
}

void Logic::loop()
{
	_timer->loop();
}

void Logic::setTargetTemperature(unsigned int temp)
{
	// Timer is not reset when temperature changes
	_targetTemperature = temp;
}

Logic::State Logic::state() const
{
	return _currentState;
}
