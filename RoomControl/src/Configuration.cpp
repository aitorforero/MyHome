#include <avr/wdt.h>
#include <EEPROM.h>
#include <string.h>

#include "Configuration.h"

bool Configuration::load()
{
	bool isValid = false;
	
	EEPROM.get(CONFIG_SIGNATURE_POS, cd);

	if (strcmp(cd.signature,CONFIG_SIGNATURE)!=0)
	{
		setSignature(CONFIG_SIGNATURE);
		setMAC(nullMAC);
		setName(CONFIG_DEFAULT_NAME);
		setMQTTServerIP(CONFIG_MQTT_SERVER_IP_LENGTH);
		setMQTTServerPort(CONFIG_DEFAULT_PORT);
		update();
	}

	return isValid ;

}

void Configuration::setSignature(const char* signature)
{ 
	for(int i = 0; i < CONFIG_SIGNATURE_LENGTH; i++)
		cd.signature[i] = signature[i];
	update();  
};

void Configuration::update()
{
	EEPROM.put(CONFIG_SIGNATURE_POS, cd);            
}
    
void Configuration::getMAC(byte* MAC)
{
	for(int i = 0; i < CONFIG_MAC_LENGTH; i++)
		MAC[i] = cd.MAC[i];
};
    
void Configuration::setMAC(const byte* MAC)
{ 
	for(int i = 0; i < CONFIG_MAC_LENGTH; i++)
		cd.MAC[i] = MAC[i];
	update();  
};

bool Configuration::getName(char* name)
{
  for(int i = 0; i < CONFIG_NAME_LENGTH; i++)
		name[i] = cd.name[i];
 };
    
void Configuration::setName(const char* name)
{ 
	for(int i = 0; i < CONFIG_NAME_LENGTH; i++)
		cd.name[i] = name[i];
	update();  
};
    
void Configuration::getMQTTServerIP(byte* serverIP)
{    
  for(int i = 0; i < CONFIG_MQTT_SERVER_IP_LENGTH; i++)
		serverIP[i] = cd.serverIP[i];
};
    
void Configuration::setMQTTServerIP(const byte* serverIP)
{    
  for(int i = 0; i < CONFIG_MQTT_SERVER_IP_LENGTH; i++)
		cd.serverIP[i] = cd.serverIP[i];
	update();  
};

int Configuration::getMQTTServerPort()
{
	return cd.serverPort;          
};

void Configuration::setMQTTServerPort(int serverPort)
{
	cd.serverPort = serverPort;        
	update();  
};

ConfigurationData Configuration::cd;
byte Configuration::nullMAC[CONFIG_MAC_LENGTH] = {0};
byte Configuration::nullIP[CONFIG_MQTT_SERVER_IP_LENGTH] = {0};
