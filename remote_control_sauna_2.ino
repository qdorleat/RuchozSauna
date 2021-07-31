//#include <ArduinoOTA.h>

#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "ctime"

#include "Timer.h"

using namespace std;

//-------------------------------------------------------------------------
// Variables definition
//-------------------------------------------------------------------------

//CONNECTIVITY
const char* ssid = "VillaRuchoz HighSpeed";   //Internet name
const char* password =  "Flocki1nTheHouse";   //Internet Password
AsyncWebServer server(80);

// SAUNA ACTUATOR
int turn_on_off=0;       // request of turning on or off by the controller
int saunaGate = 26;      // output pin for the sauna main current

// MANUAL TEMPERATURE REQUEST
const int pot_Pin = 39;              // input pin for the potentiomenter (manual temperature selection)
int pot_Value;                       // input value from the potentiometer
float pot_Voltage = 0; // measured voltage for requested temperature (potentiometer)
float Requested_Temperature = 0;    // requested temperature, in degrses

// SAUNA TEMPERATURE MEASUREMENT
const int thermo_1_Pin = 34;      // input pin for the thermistor (Sauna thermometer)
int   thermo_1_Value;             // input value from the thermistor
float thermo_1_Voltage = 0;       // analog input voltage for measured temperature
float thermo_1_Resistance = 0;    // measured resistance of the thermistor (sauna thermometer)
float Measured_Temperature_1 = 0; // measured temperature, in degrees
float p1 = 133.06;                // fit parameter for the thermistor
float p2 = 32549;                 // fit parameter for the thermistor
float p3 = 11.768;                // fit parameter for the thermistor
float p4 = 27.275;                // fit parameter for the thermistor
//-------------------------------------------------------------------------

Timer my_chrono;

class Temperature_Controller {
  const float tolerance_temperature = 5;  // the tolerance in degrees for the requested temperature, to avoid switching on and off the oven too quickly
  //BLABLA i don't get this part so much, what exactly is timeOutFunc?

public:

  // BLABLA by having a returning value, do I loose the parallel functioning
  // that i Have with the my_chrono class?
  int loop(float meas_temperature, float req_temperature) {
    
    if(static_cast<int>(meas_temperature) > req_temperature + tolerance_temperature) {
      //BLABLA stop the oven;
      return 1;}
    else if(static_cast<int>(meas_temperature) < req_temperature - tolerance_temperature) {
      //BLABLA start the oven;
      return 0;}
    else{
      // BLABLA do nothing (continue heating or staying off...)
    }
  }
};
Temperature_Controller my_controller;

void connect() {
 while (WiFi.status() != WL_CONNECTED) {
   delay(1000);
   Serial.println("Connecting to WiFi..");
 }
}

void startSauna(AsyncWebServerRequest *request) {
   my_chrono.start(&stopSauna);
   digitalWrite(saunaGate, LOW);
   if(request) {
     request->send(200, "text/plain","Sauna Started");
   }
 }

void stopSauna(AsyncWebServerRequest *request) {
  if(request) {
    request->send(200, "text/plain", "Sauna Stopped");
  }
   digitalWrite(saunaGate, HIGH);
   // BLABLA why don't we stop the timer too here? we should...
   Serial.println("Sauna Stopped");
}

bool isSaunaActive() {
  return !digitalRead(saunaGate);
}
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
// Setup and loop
//-------------------------------------------------------------------------
void setup() {
  pinMode(saunaGate, OUTPUT);    // now the pin is set to actuate the switch
  digitalWrite(saunaGate, HIGH); // BLABLA check this! maybe the swtich is inverting. The signal should be low when the sauna is off, high when the sauna is on
  Serial.begin(115200);

  Serial.println("");             // newline in the serial monitor
  WiFi.begin(ssid, password);     // Set internet and PW
  connect();                      // and connect to the wifi
  Serial.println("ESP32's assigned IP address: ");
  Serial.println(WiFi.localIP()); // exposes the ESP32's IP on the serial monitor
  Serial.println("");             // newline in the serial monitor

  // BLABLA Don't get these next 4 lines
  // set the comunications between the Server and User
  server.on("/relay/off", HTTP_GET, &stopSauna);
  server.on("/relay/on", HTTP_GET, &startSauna);
  server.on("/relay", HTTP_GET, [](AsyncWebServerRequest *request){
   request->send(200, "text/plain", isSaunaActive() ? "Sauna active" : "Sauna Inactive");
  });
  server.begin();

  Serial.println("Finished setup, starting the Controller");
  Serial.println("");
}

void loop() {
  
  my_chrono.loop();
  // BLABLA if I understood correctly,  my_chrono.start() will set the timer to zero and launch the actuator

  // BLABLA substitute this with the server request, instead of the potentiometer
  pot_Value = analogRead(pot_Pin);
  pot_Voltage = (3.3/4095.0)*pot_Value;
  Requested_Temperature = (120/4095.0)*pot_Value;

  // Now we calculate the temperature measured in the sauna
  thermo_1_Value = analogRead(thermo_1_Pin);
  thermo_1_Voltage = (3.3/4095.0)*thermo_1_Value ;
  thermo_1_Resistance = 1000*thermo_1_Voltage/(3.3-thermo_1_Voltage);

  Measured_Temperature_1 = -p4*log((thermo_1_Resistance-p1)/p2)-p3;

  turn_on_off = my_controller.loop(Measured_Temperature_1,Requested_Temperature);
  // BLABLA  do something with this turn_on_off value, make sure the timer allows!

  delay(500);
}







//  Serial.print("pot_Value: ");
//  Serial.print(pot_Value);

//  Serial.print(" Voltage potentiometer: ");
//  Serial.print(pot_Voltage);
//  Serial.print("V");

/*
  Serial.print(" Requested Temperature: ");
  Serial.print(Requested_Temperature);

  Serial.print(" thermistor: ");
  Serial.print(thermo_1_Value);

  Serial.print(" meas thermistor V: ");
  Serial.print(thermo_1_Voltage);

  Serial.print(" Measured Temperature: ");
  Serial.print(Measured_Temperature_1);
  Serial.println("deg");
//*/
