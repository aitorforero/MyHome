#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <Arduino.h>


#define CONFIG_SIGNATURE "RCtrl01"
#define CONFIG_SIGNATURE_POS 100

#define CONFIG_SIGNATURE_LENGTH 8
#define CONFIG_MAC_LENGTH 6
#define CONFIG_NAME_LENGTH 9
#define CONFIG_MQTT_SERVER_IP_LENGTH 4
#define CONFIG_ROOT_TOPIC_LENGTH 9
#define CONFIG_ROOMCONTROL_TOPIC_LENGTH 9
#define CONFIG_SERVER_TOPIC_LENGTH 9
#define CONFIG_DEFAULT_NAME "ANONIMO"
#define CONFIG_DEFAULT_PORT 1883
#define CONFIG_DEFAULT_ROOT_TOPIC "casa"
#define CONFIG_DEFAULT_ROOMCONTROL_TOPIC "mandos"
#define CONFIG_DEFAULT_SERVER_TOPIC "SRVR"



struct ConfigurationData{
  char signature[CONFIG_SIGNATURE_LENGTH];
  byte MAC[CONFIG_MAC_LENGTH];
  char name[CONFIG_NAME_LENGTH];
  byte serverIP[CONFIG_MQTT_SERVER_IP_LENGTH];
  int serverPort;
  char rootTopic[CONFIG_ROOT_TOPIC_LENGTH];
  char roomControlTopic[CONFIG_ROOMCONTROL_TOPIC_LENGTH];
  char serverTopic[CONFIG_SERVER_TOPIC_LENGTH];
};

class Configuration {
    private:
        static ConfigurationData cd;
        static void setSignature(const char* signature);
        static byte nullMAC[CONFIG_MAC_LENGTH];
        static byte nullIP[CONFIG_MQTT_SERVER_IP_LENGTH];

    public:
        static bool load();
        static void update();
    
        static void getMAC(byte* MAC);
        static void setMAC(const byte* MAC);
        static void getName(char* name);
        static void setName(const char* name);
        static void getMQTTServerIP(byte* serverIP);
        static void setMQTTServerIP(const byte* serverIP);
        static int getMQTTServerPort();
        static void setMQTTServerPort(int serverPort);
        static void getRootTopic(char* rootTopic);
        static void setRootTopic(const char* rootTopic);
        static void getRoomControlTopic(char* roomControlTopic);
        static void setRoomControlTopic(const char* roomControlTopic);
        static void getServerTopic(char* serverTopic);
        static void setServerTopic(const char* serverTopic);
};


#endif


    