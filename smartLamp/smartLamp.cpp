#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <pistache/endpoint.h>
#include <pistache/router.h>
#include <ctime>
#include <stdlib.h> 
#include <filesystem>
#include <mqtt/client.h>

using namespace std;
using namespace Pistache;
using namespace Pistache::Http;
using namespace Pistache::Rest;

class SmartLamp {
public:
    SmartLamp() {
    }
};

SmartLamp lamp;

enum Colors
{
    WHITE = 1,
    RED = 2,
    GREEN = 3,
    BLUE = 4,
    YELLOW = 5,
    PINK = 6,
    PURPLE = 7
};

std::string getColorFromNumber(int p)
{
    switch(p)
    {
    case 1:
        return "WHITE";
    case 2:
        return "RED";
    case 3:
        return "GREEN";
    case 4:
        return "BLUE";
    case 5:
        return "YELLOW";
    case 6:
        return "PINK";
    case 7:
        return "PURPLE";
    default:
        return "WHITE";
    }
}

enum Motions
{
    OFF = 1,
    FIXED = 2,
    BREATHING = 3,
    BLINK = 4
};

std::string getMotionFromNumber(int p)
{
    switch(p)
    {
    case 1:
        return "OFF";
    case 2:
        return "FIXED";
    case 3:
        return "BREATHING";
    case 4:
        return "BLINK";
    default:
        return "OFF";
    }
}

time_t now = time(0);

struct Config 
{
    bool isOn = false;
    int brightness = 50;
    Colors color;
    Motions motion;
    tm *time;
    bool autoStart = true;
}; 

std::vector<Config*> saved_Configs;


Config *defaultConfig = new Config();

void getConfigure(const Rest::Request& request, Http::ResponseWriter response)
{
    std::string returnString = "No Configuration Available!";
    auto TextParam = request.param(":configurationNumber").as<std::string>();

    if(std::all_of(TextParam.begin(), TextParam.end(), ::isdigit))
    {
        int index = stoi(TextParam);

        if (index >= saved_Configs.size() || index < 0)
        {
            returnString = "Configuration not found.";
        }
        else 
        {
            Config* config = saved_Configs[index];
            //TODO: color sa afiseze culoarea, nu numarul
            returnString = "This lamp's current configuration:\nisOn:" 
            + to_string(config->isOn) + "\n" +
            "brightness:" + to_string(config->brightness) + "\n" +
            "color:" + getColorFromNumber(config->color) + "\n" +
            "motion:" + getMotionFromNumber(config->motion) + "\n";
        }
    }
    else {
        returnString = "Param format not accepted.";
    }
    response.send(Http::Code::Ok, returnString.c_str());
}

void setConfigure(const Rest::Request& request, Http::ResponseWriter response)
{
    Config* ourConfiguration;
    auto TextParam = request.param(":configureJSON").as<std::string>();
    std::cout << "Input Received : " <<TextParam.c_str() << '\n';
    char* auxText = new char[strlen(TextParam.c_str())];
    strcpy(auxText, TextParam.c_str());
    char* token = strtok(auxText,";");
    int index = 1;

    ourConfiguration = new Config();

    while(token != NULL)
    {
        if(index == 1)
        {   
            if (strcmp(token, "-") == 0) 
            {
                ourConfiguration->isOn = defaultConfig->isOn;
            } 
            else 
            {
                ourConfiguration->isOn = strcmp(token, "1") == 0;
            }
               
        }
        else if(index == 2)
        {
            if (strcmp(token, "-") == 0) 
            {
                ourConfiguration->brightness = defaultConfig->brightness;
            } 
            else 
            {
                int brightness = atoi(token);
                ourConfiguration->brightness = brightness;
            }
        }
        else if(index == 3)
        {
            if (strcmp(token, "-") == 0) 
            {
                ourConfiguration->color = defaultConfig->color;
            } 
            else 
            {
                Colors color = (Colors)atoi(token);
                ourConfiguration->color = color;
            }
        }
        else if(index == 4)
        {
            if (strcmp(token, "-") == 0) 
            {
                ourConfiguration->motion = defaultConfig->motion;
            } 
            else 
            {
                Motions motion = (Motions)atoi(token);
                ourConfiguration->motion = motion;
            }
            
        }
        ++index;
        token = strtok(NULL, ";");
    }
    delete auxText;

    time_t now = time(0);
    ourConfiguration->time = localtime(&now);

    saved_Configs.push_back(ourConfiguration);

    std::cout << "Output : " << saved_Configs.size() - 1 << ' ' << ourConfiguration->isOn << ' ' << ourConfiguration->brightness << ' ' << getColorFromNumber(ourConfiguration->color) << ' ' << getMotionFromNumber(ourConfiguration->motion) << ' ' << ourConfiguration->time->tm_hour <<"\n";
    response.send(Http::Code::Ok, "Configuration Saved!");
}

void setDefaultConfigure(const Rest::Request& request, Http::ResponseWriter response)
{
    // Read default config
    Config* ourConfiguration;
    auto TextParam = request.param(":configureJSON").as<std::string>();
    std::cout << "Input Received : " <<TextParam.c_str() << '\n';
    char* auxText = new char[strlen(TextParam.c_str())];
    strcpy(auxText, TextParam.c_str());
    char* token = strtok(auxText,";");
    int index = 1;

    ourConfiguration = new Config();

    while(token != NULL)
    {
        if(index == 1)
        {   
            if (strcmp(token, "-") == 0) 
            {
                ourConfiguration->isOn = defaultConfig->isOn;
            } 
            else 
            {
                ourConfiguration->isOn = strcmp(token, "1") == 0;
            }
               
        }
        else if(index == 2)
        {
            if (strcmp(token, "-") == 0) 
            {
                ourConfiguration->brightness = defaultConfig->brightness;
            } 
            else 
            {
                int brightness = atoi(token);
                ourConfiguration->brightness = brightness;
            }
        }
        else if(index == 3)
        {
            if (strcmp(token, "-") == 0) 
            {
                ourConfiguration->color = defaultConfig->color;
            } 
            else 
            {
                Colors color = (Colors)atoi(token);
                ourConfiguration->color = color;
            }
        }
        else if(index == 4)
        {
            if (strcmp(token, "-") == 0) 
            {
                ourConfiguration->motion = defaultConfig->motion;
            } 
            else 
            {
                Motions motion = (Motions)atoi(token);
                ourConfiguration->motion = motion;
            }
            
        }
        ++index;
        token = strtok(NULL, ";");
    }
    delete auxText;

    time_t now = time(0);
    ourConfiguration->time = localtime(&now);

    defaultConfig = ourConfiguration;

    //Write to file
    FILE* f = fopen("DefaultConfig.txt", "w");
    if(!f)
    {
        cout<<"Default configuration not set\n";
    }

    // Determine file 
    string str = to_string(ourConfiguration->isOn) + ";" +
                to_string(ourConfiguration->brightness) + ";" +
                to_string(ourConfiguration->color) + ";" +
                to_string(ourConfiguration->motion) + ";" +
                to_string(ourConfiguration->autoStart) + ";";
    cout<< str << "\n";
    rewind(f);
    char char_array[str.length() + 1];
    strcpy(char_array, str.c_str());
    fwrite(char_array, sizeof(char), sizeof(str), f);
    fclose (f);
    


    string returnString = "This lamp's current configuration:\nisOn:" 
            + to_string(ourConfiguration->isOn) + "\n" +
            "brightness:" + to_string(ourConfiguration->brightness) + "\n" +
            "color:" + getColorFromNumber(ourConfiguration->color) + "\n" +
            "motion:" + getMotionFromNumber(ourConfiguration->motion) + "\n";

    response.send(Http::Code::Ok, returnString);
}

void updateConfigure(const Rest::Request& request, Http::ResponseWriter response)
{
    std::string returnString = "No Configuration Available!";
    auto TextParam = request.param(":configurationNumber").as<std::string>();
    if(std::all_of(TextParam.begin(), TextParam.end(), ::isdigit))
    {
        int index = stoi(TextParam);

        if (index >= saved_Configs.size() || index < 0)
        {
            returnString = "Configuration not found.";
        }
        else 
        {
            Config* ourConfiguration = saved_Configs[index];
            //TODO: color sa afiseze culoarea, nu numarul
            returnString = "This lamp's current configuration:\nisOn:" 
            + to_string(ourConfiguration->isOn) + "\n" +
            "brightness:" + to_string(ourConfiguration->brightness) + "\n" +
            "color:" + getColorFromNumber(ourConfiguration->color) + "\n" +
            "motion:" + getMotionFromNumber(ourConfiguration->motion) + "\n";

            std::cout << returnString;

            TextParam = request.param(":configureJSON").as<std::string>();
            std::cout << "Input Received : " <<TextParam.c_str() << '\n';
            char* auxText = new char[strlen(TextParam.c_str())];
            strcpy(auxText, TextParam.c_str());
            char* token = strtok(auxText,";");
            int i = 1;

            while(token != NULL)
            {
                if(i == 1)
                {   
                    if (strcmp(token, "-") == 0) 
                    {
                        ourConfiguration->isOn = defaultConfig->isOn;
                    } 
                    else 
                    {
                        ourConfiguration->isOn = strcmp(token, "1") == 0;
                    }
                    
                }
                else if(i == 2)
                {
                    if (strcmp(token, "-") == 0) 
                    {
                        ourConfiguration->brightness = defaultConfig->brightness;
                    } 
                    else 
                    {
                        int brightness = atoi(token);
                        ourConfiguration->brightness = brightness;
                    }
                }
                else if(i == 3)
                {
                    if (strcmp(token, "-") == 0) 
                    {
                        ourConfiguration->color = defaultConfig->color;
                    } 
                    else 
                    {
                        Colors color = (Colors)atoi(token);
                        ourConfiguration->color = color;
                    }
                }
                else if(i == 4)
                {
                    if (strcmp(token, "-") == 0) 
                    {
                        ourConfiguration->motion = defaultConfig->motion;
                    } 
                    else 
                    {
                        Motions motion = (Motions)atoi(token);
                        ourConfiguration->motion = motion;
                    }
                    
                }
                ++i;
                token = strtok(NULL, ";");
            }
            delete auxText;

            time_t now = time(0);
            ourConfiguration->time = localtime(&now);

            std::cout << "Output : " << index << ' ' << ourConfiguration->isOn << ' ' << ourConfiguration->brightness << ' ' << getColorFromNumber(ourConfiguration->color) << ' ' << getMotionFromNumber(ourConfiguration->motion) << ' ' << ourConfiguration->time->tm_hour <<"\n";

             returnString = "This lamp's new configuration:\nisOn:" 
            + to_string(ourConfiguration->isOn) + "\n" +
            "brightness:" + to_string(ourConfiguration->brightness) + "\n" +
            "color:" + getColorFromNumber(ourConfiguration->color) + "\n" +
            "motion:" + getMotionFromNumber(ourConfiguration->motion) + "\n";
            saved_Configs[index] = ourConfiguration;

        }
    }
    else {
        returnString = "Param format not accepted.";
    }
    response.send(Http::Code::Ok, returnString.c_str());
}

void checkTime(const Rest::Request& request, Http::ResponseWriter response)
{
    time_t now = time(0);
    tm* time = localtime(&now);
    bool setAuto = false;

    if(time->tm_hour == 18 &&  time->tm_min == 0 && time->tm_sec == 0)
    {
        for(int i = 0; i < saved_Configs.size(); i++)
        {
            saved_Configs[i]->autoStart = true;
        }
        setAuto = true;
    }

    if(time->tm_hour == 24 &&  time->tm_min == 0 && time->tm_sec == 0)
    {
        for(int i = 0; i < saved_Configs.size(); i++)
        {
            saved_Configs[i]->autoStart = true;
        }

        setAuto = true;
    }

    if(saved_Configs[0]->autoStart)
    {
        if (time->tm_hour> 18 && time->tm_hour< 24)
        {
            for(int i = 0; i < saved_Configs.size(); i++)
            {
                saved_Configs[i]->time = time;
                saved_Configs[i]->isOn = true;
            }
        }
        else
        {
            for(int i = 0; i < saved_Configs.size(); i++)
            {
                saved_Configs[i]->time = time;
                saved_Configs[i]->isOn = false;
            }
        }
    }
    std::string returnString = "Locale time: " + to_string(time->tm_hour) + ":" + to_string(time->tm_min) + ":" + to_string(time->tm_sec) + "\n";
    if(setAuto)
    {
        returnString += "The lamp is on auto mode.\n";
    }
    
    response.send(Http::Code::Ok, returnString.c_str());
}

void deleteConfigure(const Rest::Request& request, Http::ResponseWriter response)
{
    std::string returnString = "No Configuration Available!";
    auto TextParam = request.param(":configurationNumber").as<std::string>();

    if(std::all_of(TextParam.begin(), TextParam.end(), ::isdigit))
    {
        int index = stoi(TextParam);

        if (index >= saved_Configs.size() || index < 0)
        {
            returnString = "Configuration not found.";
        }
        else 
        {
            Config* config = saved_Configs[index];

            saved_Configs.erase(saved_Configs.begin() + index);
            returnString = "Successfuly deleted. \nDeleted lamp's configuration:\nisOn:" 
            + to_string(config->isOn) + "\n" +
            "brightness:" + to_string(config->brightness) + "\n" +
            "color:" + getColorFromNumber(config->color) + "\n" +
            "motion:" + getMotionFromNumber(config->motion) + "\n";
        }
    }
    else {
        returnString = "Param format not accepted.";
    }
    response.send(Http::Code::Ok, returnString.c_str());
}

void clap(const Rest::Request& request, Http::ResponseWriter response)
{
    std::string returnString = "No Configuration Available!";
    auto TextParam = request.param(":configurationNumber").as<std::string>();
    if(std::all_of(TextParam.begin(), TextParam.end(), ::isdigit))
    {
        int index = stoi(TextParam);

        if (index >= saved_Configs.size() || index < 0)
        {
            returnString = "Configuration not found.";
        }
        else 
        {
            Config* ourConfiguration = saved_Configs[index];
            returnString = "This lamp's current configuration:\nisOn:" 
            + to_string(ourConfiguration->isOn) + "\n" +
            "brightness:" + to_string(ourConfiguration->brightness) + "\n" +
            "color:" + getColorFromNumber(ourConfiguration->color) + "\n" +
            "motion:" + getMotionFromNumber(ourConfiguration->motion) + "\n";
            std::cout << returnString;

            if(ourConfiguration->isOn)
            {
                ourConfiguration->isOn = false;
                returnString = "The lamp is turned off now.";
            }
            else
            {
                ourConfiguration->isOn = true;
                returnString = "The lamp is turned on now.";
            }
            ourConfiguration->autoStart = false;
        }
    }
    else {
        returnString = "Param format not accepted.";
    }
    response.send(Http::Code::Ok, returnString.c_str());
}

void mqttExample() {
    const std::string address = "localhost";
    const std::string clientId = "lamp";

    // Create a client
    mqtt::client client(address, clientId);

    mqtt::connect_options options;
    options.set_keep_alive_interval(20);
    options.set_clean_session(true);

    try {
        // Connect to the client
        client.connect(options);

        // Create a message
        const std::string TOPIC = "lamp";
        const std::string PAYLOAD = "Connected to the lamp!";
        auto msg = mqtt::make_message(TOPIC, PAYLOAD);

        // Publish it to the server
        client.publish(msg);

        // Disconnect
        client.disconnect();
    }
    catch (const mqtt::exception& exc) {
        std::cerr << exc.what() << " [" << exc.get_reason_code() << "]" << std::endl;
    }
}

int main() {
    // Set up routes
    Router router;

    router.post("/configure/:configureJSON", Routes::bind(setConfigure));
    router.post("/configureDefault/:configureJSON", Routes::bind(setDefaultConfigure));
    router.post("/configure/:configurationNumber/:configureJSON", Routes::bind(updateConfigure));
    router.get("/configure/:configurationNumber", Routes::bind(getConfigure));
    router.get("/deleteConfigure/:configurationNumber", Routes::bind(deleteConfigure));
    router.get("/timeChecker", Routes::bind(checkTime));
    router.post("/clap/:configurationNumber", Routes::bind(clap));
    //----------------------------------------------------------------------
    // Configure server
    const string host = "localhost";
    const Port port = 9080;

    Address address(host, port);
    Endpoint endpoint(address);
    endpoint.init();
    endpoint.setHandler(router.handler());

    // Start server
    cout << "Server listening on http://" << host << ':' << port << '\n';
    cout << "Press Ctrl + C to quit\n";

    // Read default config
    FILE* f = fopen("DefaultConfig.txt", "r");
    if(!f)
    {
        cout<<"Default configuration not set\n";
    }

    // Determine file 
    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    char* str = new char[size];

    rewind(f);
    fread(str, sizeof(char), size, f);
    cout<< str << "\n";

    mqttExample();

    //Split ;
    // Returns first token 
    char *token = strtok(str, ";");
   
    // Keep printing tokens while one of the
    // delimiters present in str[].
    int index = 1;
    while (token != NULL)
    {
        printf("%s\n", token);
        
        if (index == 1)
        {
            defaultConfig->isOn = strcmp(token, "1") == 0;
        } else if (index == 2)
        {
            defaultConfig->brightness = atoi(token);
        } else if (index == 3)
        {
            Colors color = (Colors)atoi(token);
            defaultConfig->color = color;
        } else if (index == 4)
        {
            Motions motion = (Motions)atoi(token);
            defaultConfig->motion = motion;
        }
        else if (index == 5)
        {
            defaultConfig->autoStart = atoi(token) != 0;
        }
        index ++;
        token = strtok(NULL, ";");
    }
    time_t now = time(0);
    defaultConfig->time = localtime(&now);
    
    delete[] str;
    fclose(f);
   
    cout <<"\n";
    endpoint.serve();
}
