#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <Arduino.h>


#define CONFIG_SIGNATURE "RCtrl00"
#define CONFIG_SIGNATURE_POS 100

#define CONFIG_SIGNATURE_LENGTH 8
#define CONFIG_MAC_LENGTH 6
#define CONFIG_NAME_LENGTH 9
#define CONFIG_MQTT_SERVER_IP_LENGTH 4
#define CONFIG_DEFAULT_NAME "ANONIMO"
#define CONFIG_DEFAULT_PORT 0


struct ConfigurationData{
  char signature[CONFIG_SIGNATURE_LENGTH];
  byte MAC[CONFIG_MAC_LENGTH];
  char name[CONFIG_NAME_LENGTH];
  byte serverIP[CONFIG_MQTT_SERVER_IP_LENGTH];
  int serverPort;
};

class Configuration {
    private:
        static ConfigurationData cd;
        static void setSignature(const char* name);
        static byte nullMAC[CONFIG_MAC_LENGTH];
        static byte nullIP[CONFIG_MQTT_SERVER_IP_LENGTH];

    public:
        static bool load();
        static void update();
    
        static void getMAC(byte* MAC);
        static void setMAC(const byte* MAC);
        static bool getName(char* name);
        static void setName(const char* name);
        static void getMQTTServerIP(byte* serverIP);
        static void setMQTTServerIP(const byte* serverIP);
        static int getMQTTServerPort();
        static void setMQTTServerPort(int serverPort);
};


#endif


    