# Smart-Lamp-IoT

## Raport de analiza

Raportul de analiza a proiectului se gaseste [aici](https://github.com/AndraRaco/Smart-Lamp-IoT/blob/main/Raport%20de%20analiza%202021.docx).

## Getting started

Git clone this project to your machine.

### Prerequisites
- C++ compiler capable of building projects using C++ 17 or up
- Pistache build 002 from 20210409 or up
- Due to Pistache's current OS support a device running MacOS or Linux is required
- [QOL] Postman or any API calling software

Build tested on Ubuntu Server. You need to install Pistache library and C++ 17 compiler. 

## Building

- Go to folder's location on your machine
- Run this comand in terminal: 

  - g++ smartLamp.cpp -o smartLamp -lpistache -lcrypto -lssl -lpthread -std=c++17 -lpaho-mqttpp3 -lpaho-mqtt3a
  
  - `paho-mqttpp3` is the Paho C++ client library, and `paho-mqtt3a` is the C library it depends on (for MQTT)
  
- In a separate terminal, start the Mosquitto server:

```sh
mosquitto -v
```

The `-v` argument stands for verbose. Detailed logs are provided this way.
  
- Run this command after: 

  - ./smartLamp

## Build with

- [Pistache](https://github.com/pistacheio/pistache) - Web Server

## JSON Specifications for Routes

JSON Specifications can be found [here](https://github.com/AndraRaco/Smart-Lamp-IoT/blob/main/JSON%20Specifications.json).

## App's functionalities

- Add a new configuration (turn on/off the lamp, set brightness, set colour and motion). 
  - first parameter (isOn) is 0 for off, 1 for on;
  - second parameter is for brightness; Can be any number from 0 to 100;
  - thirs parameter is for colour; Can be any number from 1 to 7; WHITE = 1, RED = 2, GREEN = 3, BLUE = 4, YELLOW = 5, PINK = 6, PURPLE = 7;
  - forth parameter is for motion; Can be any number from 1 to 4; OFF = 1, FIXED = 2, BREATHING = 3, BLINK = 4;

- Updates an existing configuration (turn on/off the lamp, set brightness, set colour and motion for a given specification). 
  - first parameter is the ConfigurationNumber; If is out of range => error message
  - second parameter (isOn) is 0 for off, 1 for on;
  - third parameter is for the new brightness; Can be any number from 0 to 100;
  - forth parameter is for the colour; Can be any number from 1 to 7; WHITE = 1, RED = 2, GREEN = 3, BLUE = 4, YELLOW = 5, PINK = 6, PURPLE = 7;
  - fifth parameter is for the new motion; Can be any number from 1 to 4; OFF = 1, FIXED = 2, BREATHING = 3, BLINK = 4;

- Starts the device when hears a clap sound, with a specific configuration 
  - first parameter is the ConfigurationNumber; If is out of range => error message;
 
- Prints a spcific configuration 
  - first parameter is the ConfigurationNumber; If is out of range => error message <br>
  
     Example for output:
     <br>
     "This lamp's current configuration: <br>
      isOn:1 <br>
      brightness:54 <br>
      color:GREEN <br>
      motion:FIXED"
      
- Deletes a spcific configuration 
  - first parameter is the ConfigurationNumber; If is out of range => error message <br>
  
     Deletes the configuration and prints a message: <br>
     "Successfuly deleted. <br>
      Deleted lamp's configuration: <br>
      isOn:1 <br>
      brightness:54 <br>
      color:GREEN <br>
      motion:FIXED""
      
## Stateful App

The app comes with some default configurations which can be found in ConfigurationDefault file (0;67;1;1;1). This means that the lamp will be switched off, will have the brightness set to 67%, colour will be white and motion will be off. The last parameter means the autoStart property is on, that means that the lamp will automatically switch on between 18 and 24. 

If the user decides to add another configuration (SetConfig method), the default configuration will be overwritten, thus saving the last confiration. If the configuration has '-' instead of a value, the correspinding value will be left as default. The same thing happens when the user tries to update a configuration. The last configuration will be written in the file, thus overwritting the default configuration.   

#### MQTT

For MQTT protocol support, you can use the Eclipse [Paho](https://www.eclipse.org/paho) client library. The [Paho C++ library](https://github.com/eclipse/paho.mqtt.cpp#unix-and-linux) can be installed from source (will require you to also build and install the Paho C library).

MQTT sends messages to a server, therefore having a server is required. For this, you can use Eclipse [Mosquitto](https://mosquitto.org/).

Installation on Ubuntu:
```
sudo apt-add-repository ppa:mosquitto-dev/mosquitto-ppa
sudo apt update
sudo apt install mosquitto
```

## Membrii echipei

- Condurachi Corina
- Lungu Andrei
- Perju Ciprian 
- Racovita Andra-Georgiana
- Sandulescu Mihail
