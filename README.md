# Smart-Lamp-IoT

## Raport de analiza

Raportul de analiza a proiectului se gaseste [aici](https://github.com/AndraRaco/Smart-Lamp-IoT/blob/main/Raport%20de%20analiza%202021.docx).

## Getting started

Git clone this project to your machine.

### Prerequisites (de adaugat cv aici)

Build tested on Ubuntu Server. You need to install Pistache library and C++ 17 compiler. 


## Building

- Go to folder's location on your machine
- Run this comand in terminal: 

  - g++ smartLamp.cpp -o smartLamp -lpistache -lcrypto -lssl -lpthread -std=c++17
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

## Membrii echipei

- Condurachi Corina
- Lungu Andrei
- Perju Ciprian 
- Racovita Andra-Georgiana
- Sandulescu Mihail
