#include <Arduino.h>
#include "Configuration.h"
#include <EEPROM.h>

//    static ConfigData _Configuration;
bool Configuration::readFromEEPROM()
{
    for (unsigned int t=0; t<sizeof(_Configuration); t++)
        *((char*)&_Configuration + t) = EEPROM.read(CONFIGURATION_ADDRESS + t);
   
   
    String readSignature = String(_Configuration.signature);
     
    return readSignature.equals(CONFIGURATION_SIGNATURE);
};

void Configuration::saveToEEPROM()
{
    for(int i=0; i<6; i++)
      _Configuration.signature[i] = CONFIGURATION_SIGNATURE[i];
  
    for (unsigned int t=0; t<sizeof(_Configuration); t++)
        EEPROM.write(CONFIGURATION_ADDRESS + t,*((char*)&_Configuration + t));

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
  return _Configuration.MACAddress;
};

byte* Configuration::getIPAddress()
{
  return _Configuration.IPAddress;
};

String Configuration::getZone()
{
  return String(_Configuration.zone);
};

MQTTServer Configuration::getServer()
{
  return _Configuration.server;
};

void Configuration::setMACAddress(byte* newMACAddress)
{
  for(int i=0; i<6; i++)
    _Configuration.MACAddress[i] = newMACAddress[i];
};

void Configuration::setIPAddress(byte* newIPAddress)
{
  for(int i=0; i<4; i++)
    _Configuration.IPAddress[i] = newIPAddress[i];

};

void Configuration::setZone(String newZone)
{
  newZone.toCharArray(_Configuration.zone, 30);
};

void Configuration::setServer(MQTTServer newServer)
{
  _Configuration.server = newServer;
};