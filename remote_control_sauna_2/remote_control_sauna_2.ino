#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "ctime"

using namespace std;

//const char* ssid = "VillaRuchoz HighSpeed";  //replace
//const char* password =  "Flocki1nTheHouse"; //replace
const char* ssid = "wifigorilla";  //replace
const char* password =  "piercoda"; //replace
AsyncWebServer server(80);
int relayPin = 26;

const int potPin = 39; // analog input pin for the potentiomenter
float voltage = 0;
float temperature = 0;
int potValue;

class Chrono
{
  static const int COUNTER_DURATION = 5; // 60 /* MINUTES */ * 60 /* SECONDS */;
  time_t _startTimeS;
  bool isActive = false;
  

  void (*timeOutFunc)(AsyncWebServerRequest*); 

public:

  void stop()
  {
    if(timeOutFunc)
    {
      timeOutFunc(nullptr);
    }
  }
  
  void start(void (*stop)(AsyncWebServerRequest*))
  {
    _startTimeS = time(nullptr);
    timeOutFunc = stop;
  }

  void loop()
  {
    auto currentTimeS = time(nullptr);
  
    time_t durationS = currentTimeS - _startTimeS;

    if(static_cast<int>(durationS) > COUNTER_DURATION)
    {
      stop();
    }
  }
};

Chrono my_chrono;

void connect()
{
 while (WiFi.status() != WL_CONNECTED)
 {
   delay(1000);
   Serial.println("Connecting to WiFi..");
 }
}

void startSauna(AsyncWebServerRequest *request)
{
   my_chrono.start(&stopSauna);
   digitalWrite(relayPin, LOW);
   if(request)
   {
     request->send(200, "text/plain","Sauna Started");
   }
 }

void stopSauna(AsyncWebServerRequest *request)
{
  if(request)
  {
    request->send(200, "text/plain", "Sauna Stopped");
  }
   digitalWrite(relayPin, HIGH);
   Serial.println("Sauna Stopped");
}

bool isSaunaActive()
{
  return !digitalRead(relayPin);
}

void setup()
{
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  connect();


 Serial.println(WiFi.localIP());
 server.on("/relay/off", HTTP_GET, &stopSauna);
 server.on("/relay/on", HTTP_GET, &startSauna);
 server.on("/relay", HTTP_GET, [](AsyncWebServerRequest *request){
   request->send(200, "text/plain", isSaunaActive() ? "Sauna active" : "Sauna Inactive");
 });
 server.begin();
}

void loop()
{
  my_chrono.loop();  

  potValue = analogRead(potPin);
  voltage = (3.3/4095.0)*potValue;
  temperature = (110/4095.0)*potValue;

  Serial.print("potValue: ");
  Serial.print(potValue);

  Serial.print(" Voltage: ");
  Serial.print(voltage);
  Serial.print("V");

  Serial.print(" Temperature: ");
  Serial.print(temperature);
  Serial.println("°");


  delay(50);

}
