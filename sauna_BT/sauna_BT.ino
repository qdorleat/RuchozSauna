
/*
Helloooooo!!
*/

#include "BluetoothSerial.h"
#include "Timer.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial remoteCommand;
int received;// received value will be stored in this variable
char receivedChar;// received value will be stored as CHAR in this variable

const char turnON = 'a';
const char turnOFF = 'b';
const int tempC = 0;
int Sauna_state = 0;
const int SaunaCMD = 26;
const int T_in = 34;
int T_integer = -99;
float a = -0.0334448161;
float b = 121.070234282;
float T_celsius = 0; // T = a*V + b
Timer timer;
int time_left_s = 0;

void setup() {
  Serial.begin(115200);
  remoteCommand.begin("ESP32_Robojax"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  Serial.println("To turn ON send: a");//print on serial monitor
  Serial.println("To turn OFF send: b"); //print on serial monitor
  pinMode(SaunaCMD, OUTPUT);
}

void Off()
{
  digitalWrite(SaunaCMD, LOW);// turn the LED off
  Sauna_state = 0;
  remoteCommand.println("OFF Command received: ACK");// write on BT app
  Serial.println("OFF Command received:");//write on serial monitor
}

void On()
{
  digitalWrite(SaunaCMD, HIGH);// turn the LED ON
  Sauna_state = 1;
  remoteCommand.println("ON Command received: ACK");// write on BT app
  Serial.println("ON Command Received");//write on serial monitor

  timer.start(&Off, &time_left_s);
}
void loop()
{
  receivedChar = (char)remoteCommand.read();
  T_integer = analogRead(T_in);
  T_celsius = a*T_integer+b;
  
  Serial.print ("Sauna: ");//print on serial monitor
  Serial.print (Sauna_state);//print on serial monitor
  Serial.print (",\t t: ");//print on serial monitor
  Serial.print (time_left_s);//print on serial monitor
  Serial.print (",\t T:");//print on serial monitor
  Serial.println(T_celsius);//print on serial monitor
  
  remoteCommand.print("Sauna: ");// write on BT app
  remoteCommand.print(Sauna_state);// write on BT app
  remoteCommand.print(",\t t: ");// write on BT app
  remoteCommand.print(time_left_s);// write on BT app
  remoteCommand.print(",\t T: ");// write on BT app
  remoteCommand.println(T_celsius);// write on BT app

  timer.loop();

  if (Serial.available())
  {
    remoteCommand.write(Serial.read());
  }
  if (remoteCommand.available())
  {
    remoteCommand.print("Received:");// write on BT app
    remoteCommand.println(receivedChar);// write on BT app
    Serial.print ("Received:");//print on serial monitor
    Serial.println(receivedChar);//print on serial monitor
    //remoteCommand.println(receivedChar);//print on the app
    //remoteCommand.write(receivedChar); //print on serial monitor
    if (receivedChar == turnON)
    {
      On();
    }
    if (receivedChar == turnOFF)
    {
      Off();
    }
  }
  delay(500);
}
