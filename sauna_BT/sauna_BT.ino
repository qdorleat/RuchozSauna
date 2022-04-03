/*
 * Turn LED ON or OFF from your phone
 * 
 * Using ESP32's Bluetooth and Mobile app
 * turn ON and OFF LED
 * 
 * Updated/Written by Ahmad Shamshiri 
 * On August 25, 2019 in Ajax, Ontario, Canada
 * Watch video instruction for this cod:
 * https://youtu.be/4OOFlS75owA
 * www.Robojax.com 
 * 
 Get this code and other Arduino codes from Robojax.com
Learn Arduino step by step in structured course with all material, wiring diagram and library
all in once place. Purchase My course on Udemy.com http://robojax.com/L/?id=62

If you found this tutorial helpful, please support me so I can continue creating 
content like this. You can support me on Patreon http://robojax.com/L/?id=63

or make donation using PayPal http://robojax.com/L/?id=64

 *  * This code is "AS IS" without warranty or liability. Free to be used as long as you keep this note intact.* 
 * This code has been download from Robojax.com
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see .
 */

//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that remoteCommand have the same functionalities of a normal Serial

#include "BluetoothSerial.h"
#include "Timer.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial remoteCommand;
int received;// received value will be stored in this variable
char receivedChar;// received value will be stored as CHAR in this variable

const char turnON ='a';
const char turnOFF ='b';
const int tempC = 0;
const int LEDpin = 23;
Timer timer;

void setup() {
  Serial.begin(115200);
  remoteCommand.begin("ESP32_Robojax"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  Serial.println("To turn ON send: a");//print on serial monitor  
  Serial.println("To turn OFF send: b"); //print on serial monitor 
  pinMode(LEDpin, OUTPUT);
}

void Off()
{
	remoteCommand.println("OFF Command received: ACK");// write on BT app
	Serial.println("ON Command received:");//write on serial monitor
	digitalWrite(LEDpin, LOW);// turn the LED off
}

void On()
{
	remoteCommand.println("ON Command received: ACK");// write on BT app
	Serial.println("ON Command Received");//write on serial monitor
	digitalWrite(LEDpin, HIGH);// turn the LED ON

	timer.start(&Off);
}
void loop()
{
	receivedChar =(char)remoteCommand.read();

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
		if(receivedChar == turnON)
		{
			On();
		}
		if(receivedChar == turnOFF)
		{
			Off();
		}
	}
	delay(20);
}
