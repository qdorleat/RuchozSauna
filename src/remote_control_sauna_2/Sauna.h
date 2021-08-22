#ifndef SAUNA_H
#define SAUNA_H

#include "Logic.h"

class Sauna
{
public:

  static Sauna* get();

	void on_OnPressed();

	void on_OffPressed();

	void on_temperatureReceived(unsigned int temp);

	void run();
	
	void loop();

private:

	Logic _logic;
  static Sauna* _sauna;
};

#endif
