#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <Arduino.h>

#define CONFIG_SIGNATURE "RCtrl00"
#define CONFIG_SIGNATURE_LENGTH 7
#define CONFIG_MAX_LENGTH 100

#define CONFIG_NAME_LENGTH 8

class Configuration {
    private:
        static const char * _signature = "RCtrl00";
        static byte _mac[6]; 
        static char _Name[CONFIG_NAME_LENGTH+1]; 
        static byte _MQTTserverIP[4];
        static int _MQTTserverPort;
    
    

    public:
        static byte* getMAC();
        static void getName(char* name);
        static void setName(const char* name);
        static byte* getMQTTServerIP();
        static int getMQTTServerPort();
        static void save();
        static bool load();
};

#endif


    