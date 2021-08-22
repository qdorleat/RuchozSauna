#include "ESPAsyncWebServer.h"
#include "/snap/arduino/56/libraries/WiFi/src/WiFi.h"

static const char* ssid = "VillaRuchoz HighSpeed";   //Internet name
static const char* password =  "Flocki1nTheHouse";   //Internet Password

void startSauna(AsyncWebServerRequest *request) {
  /*
  my_chrono.start(&stopSauna);
  digitalWrite(saunaGate, LOW);
  if(request) {
    request->send(200, "text/plain","Sauna Started");
  }
  */
  //Sauna::get()->on_OnPressed();
}

void stopSauna(AsyncWebServerRequest *request) {
/*
if(request) {
  request->send(200, "text/plain", "Sauna Stopped");
}
 digitalWrite(saunaGate, HIGH);
 // BLABLA why don't we stop the timer too here? we should...
 Serial.println("Sauna Stopped");
*/
  //Sauna::get()->on_OffPressed();
}

class WifiRuchoz
{
  public:
  
	WifiRuchoz(
	  
	          //  (*stopSauna)(AsyncWebServerRequest*),
				    // (*startSauna)(AsyncWebServerRequest*)
				     )
	{
		_server = new AsyncWebServer(80);

		// set the comunications between the Server and User
		_server->on("/relay/off", HTTP_GET, &stopSauna);
		_server->on("/relay/on", HTTP_GET, &startSauna);
		/*
		_server.on("/relay", HTTP_GET, [](AsyncWebServerRequest *request) {
			request->send(200, "text/plain", isSaunaActive() ? "Sauna active" : "Sauna Inactive");
		});
		*/
	}

	void connect()
	{
		WiFi.begin(ssid, password);

		while (WiFi.status() != WL_CONNECTED)
		{
			delay(1000);
			Serial.println("Connecting to WiFi..");
		}

		Serial.println("ESP32's assigned IP address: ");
		Serial.println(WiFi.localIP()); // exposes the ESP32's IP on the serial monitor
		Serial.println("");             // newline in the serial monitor

		_server->begin();
	}

private:
	AsyncWebServer* _server;
};
