#include "Sauna.h"

Sauna* Sauna::_sauna = nullptr;

Sauna* Sauna::get()
{
  if(!_sauna)
  {
    _sauna = new Sauna();
  }
  return _sauna;
}

void Sauna::on_OnPressed()
{
	_logic.on_OnPressed();
}

void Sauna::on_OffPressed()
{
	_logic.on_OffPressed();
}

void Sauna::on_temperatureReceived(unsigned int temp)
{
	_logic.setTargetTemperature(temp);
}

void Sauna::run()
{
	_logic.run();
}

void Sauna::loop()
{
	_logic.loop();
}
