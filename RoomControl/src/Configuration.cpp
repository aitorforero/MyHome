#include "Configuration.h"
#include <avr/wdt.h>
#include <EEPROM.h>
#include <string.h>

     
byte Configuration::_mac[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
char Configuration::_Name[9] = "ANONIMO";
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

void Configuration::getName(char* name){
    strncpy(name, _Name, CONFIG_NAME_LENGTH );
};

void Configuration::setName(const char* value){
    strncpy(_Name, value, CONFIG_NAME_LENGTH );
};

byte* Configuration::getMQTTServerIP(){
    return _MQTTserverIP;
};

int Configuration::getMQTTServerPort(){
    return _MQTTserverPort;
};

