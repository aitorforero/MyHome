#include "Configuration.h"
#include <EEPROM.h>

bool Configuration::isPresent()
{
  int configurationSignature = 0;
  configurationSignature = EEPROM.read(CONFIGURATION_ADDRESS) * 4 + EEPROM.read(CONFIGURATION_ADDRESS+1) * 2 + EEPROM.read(CONFIGURATION_ADDRESS+2)
  if(configurationSignature==CONFIGURATION_SIGNATURE)
  {
    return true;
  }
  else
  {
    return false;
  }
}

char* Configuration::getMACAddress(){}
void Configuration::setMACAddress(char* newAddress){}