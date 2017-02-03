#define byte uint8_t

#ifndef mConfiguration_h_
#define mConfiguration_h_


#include <Arduino.h>


#define CONFIGURATION_ADDRESS 0x0
#define CONFIGURATION_SIGNATURE "CWS000"


struct MQTTServer
{
    char IPAddress[4];
    int port;
};

struct ConfigData
{
    char signature[6];
    byte MACAddress[6];
    byte IPAddress[4];
    char zone[30];
    MQTTServer server;
};


class Configuration
{
  private:
    static bool readFromEEPROM();
    static void saveToEEPROM();
    static ConfigData mConfiguration;
    
   public:
    static bool load();
    static void save();
    static byte* getMACAddress();
    static byte* getIPAddress();
    static String getZone();
    static MQTTServer getServer();
    static void setMACAddress(byte* newMACAddress);
    static void setIPAddress(byte* newIPAddress);
    static void setZone(String newZone);
    static void setServer(MQTTServer newServer);

  
    
};







#endif