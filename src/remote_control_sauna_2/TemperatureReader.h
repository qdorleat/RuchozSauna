

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


void loop() {
  
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
