#include <Arduino.h>
#include "Configuration.h"
#include <EEPROM.h>

ConfigData Configuration::mConfiguration;

bool Configuration::readFromEEPROM()
{
    for (unsigned int t=0; t<sizeof(Configuration::mConfiguration); t++)
        *((char*)&Configuration::mConfiguration + t) = EEPROM.read(CONFIGURATION_ADDRESS + t);
   
   
    String readSignature = String(Configuration::mConfiguration.signature);
     
    return readSignature.equals(CONFIGURATION_SIGNATURE);
};

void Configuration::saveToEEPROM()
{
    for(int i=0; i<6; i++)
      Configuration::mConfiguration.signature[i] = CONFIGURATION_SIGNATURE[i];
  
    for (unsigned int t=0; t<sizeof(Configuration::mConfiguration); t++)
        EEPROM.write(CONFIGURATION_ADDRESS + t,*((char*)&Configuration::mConfiguration + t));

};   
    
bool Configuration::load()
{
    return readFromEEPROM();
};
void Configuration::save()
{
    saveToEEPROM();
};

byte* Configuration::getMACAddress()
{
  return Configuration::mConfiguration.MACAddress;
};

byte* Configuration::getIPAddress()
{
  return Configuration::mConfiguration.IPAddress;
};

String Configuration::getZone()
{
  return String(Configuration::mConfiguration.zone);
};

MQTTServer Configuration::getServer()
{
  return Configuration::mConfiguration.server;
};

void Configuration::setMACAddress(byte* newMACAddress)
{
  for(int i=0; i<6; i++)
    Configuration::mConfiguration.MACAddress[i] = newMACAddress[i];
};

void Configuration::setIPAddress(byte* newIPAddress)
{
  for(int i=0; i<4; i++)
    Configuration::mConfiguration.IPAddress[i] = newIPAddress[i];
};

void Configuration::setZone(String newZone)
{
  newZone.toCharArray(Configuration::mConfiguration.zone, 30);
};

void Configuration::setServer(MQTTServer newServer)
{
  Configuration::mConfiguration.server = newServer;
};