# RuchozSauna
Code for Ruchoz Sauna

## Prerequisites

* `sudo apt install python`
* `sudo pip install pyserial serial`

*Tutorial with sample code for creating arduino project 
 https://create.arduino.cc/projecthub/benjineering/easy-iot-remotely-controlling-esp32-using-an-android-app-99a1dd*

Short explanations bellow:

## Installation

### Setup ESP32 board

1. Add in Preferences The following addresses for additional Board Manager URL : https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json

2. Install Board ESP32

Tools > Board > Board Manager > Search for ESP32

3. Switch to ESP32 board in the ArduinoIDE 

Tools > Board > ESP32 Arduino > *ESP32 Dev Module*

### Attach Wifi Library and AsyncTCP dependency

1. Download  zip file from https://github.com/me-no-dev/ESPAsyncWebServer (It has to be the zip because ArduinoIDE only includes library from a zip file)

Skecth > Include Library > Add .zip Library

2. Download the following dependency : https://github.com/me-no-dev/AsyncTCP and add it to ArduinoIDE as well

### Set ArduinoIDE onto USB0

Tools > Port > /dev/ttyUSB0

In case you do not have the rights, you can add them to the dialout & tty groups :

* `sudo gpasswd --add $USER dialout`
* `sudo usermod -a -G tty $USER`