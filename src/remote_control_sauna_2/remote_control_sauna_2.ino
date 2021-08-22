#include "ESPAsyncWebServer.h"
#include "Sauna.h"
#include "WifiRuchoz.h"


//-------------------------------------------------------------------------
// Variables definition
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
// Setup and loop
//-------------------------------------------------------------------------
void setup()
{

  WifiRuchoz wifi;
  wifi.connect();
  
  Serial.begin(115200);

  Sauna::get()->run();

  Serial.println("Finished setup, starting the Controller");
  Serial.println("");
}

void loop()
{
    Sauna::get()->loop();

    delay(500);
}
