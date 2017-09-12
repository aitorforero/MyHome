#include "Configuration.h"
#include <avr/wdt.h>
#include <EEPROM.h>


byte Configuration::_mac[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
char Configuration::_Name[9] = "";
byte Configuration::_MQTTserverIP[4] = {0,0,0,0};
int Configuration::_MQTTserverPort = 0;


bool Configuration::load(){
    return false;
};

void Configuration::save(){
    // Save configuration here
};

byte* Configuration::getMAC(){
    return _mac;
};

char* Configuration::getName(){
    return _Name;
};

byte* Configuration::getMQTTServerIP(){
    return _MQTTserverIP;
};

int Configuration::getMQTTServerPort(){
    return _MQTTserverPort;
};

