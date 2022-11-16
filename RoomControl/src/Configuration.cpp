#include <DebugUtils.h>
#include <avr/wdt.h>
#include <EEPROM.h>
#include <string.h>
#include "Configuration.h"

bool Configuration::load()
{
	bool isValid = false;
	
	EEPROM.get(CONFIG_SIGNATURE_POS, cd);

//	if (strcmp(cd.signature,CONFIG_SIGNATURE)!=0)
//	{
		setSignature(CONFIG_SIGNATURE);
		setMAC(nullMAC);
		setName(CONFIG_DEFAULT_NAME);
		setRootTopic(CONFIG_DEFAULT_ROOT_TOPIC);
		setRoomControlTopic(CONFIG_DEFAULT_ROOMCONTROL_TOPIC);
		setMQTTServerIP(nullIP);
		setMQTTServerPort(CONFIG_DEFAULT_PORT);
		update();
//	} else {
		isValid = true;
//	}

	return isValid ;
}

void Configuration::setSignature(const char* signature)
{
	strncpy(cd.signature, signature, CONFIG_SIGNATURE_LENGTH);
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
	DEBUG_PRINT( "Saving MAC")  
	for(int i = 0; i < CONFIG_MAC_LENGTH; i++)
		cd.MAC[i] = MAC[i];
	update();  
};

void Configuration::getName(char* name)
{
	DEBUG_PRINT("getting name...")  	
	strncpy(name, cd.name, CONFIG_NAME_LENGTH);
	DEBUG_PRINT("got!")  	
};
    
void Configuration::setName(const char* name)
{ 
	DEBUG_PRINT("Saving Name")  
	strncpy(cd.name, name, CONFIG_NAME_LENGTH);
	update();  
};
    
void Configuration::getMQTTServerIP(byte* serverIP)
{    
  for(int i = 0; i < CONFIG_MQTT_SERVER_IP_LENGTH; i++)
		serverIP[i] = cd.serverIP[i];
};
    
void Configuration::setMQTTServerIP(const byte* serverIP)
{  	
	DEBUG_PRINT( "Saving MQTT Server IP")  
	for(int i = 0; i < CONFIG_MQTT_SERVER_IP_LENGTH; i++)
		cd.serverIP[i] = serverIP[i];
	
	update();  
};

int Configuration::getMQTTServerPort()
{
	return cd.serverPort;          
};

void Configuration::setMQTTServerPort(int serverPort)
{
	DEBUG_PRINT( "Saving MQTT Server Port")
	cd.serverPort = serverPort;        
	update();  
};


void Configuration::getRootTopic(char* rootTopic){
	strncpy(rootTopic, cd.rootTopic, CONFIG_ROOT_TOPIC_LENGTH);
};

void Configuration::setRootTopic(const char* rootTopic){
	strncpy(cd.rootTopic, rootTopic, CONFIG_ROOT_TOPIC_LENGTH);
	update();  	
};

void Configuration::getRoomControlTopic(char* roomControlTopic){
	strncpy(roomControlTopic, cd.roomControlTopic, CONFIG_ROOMCONTROL_TOPIC_LENGTH);
};

void Configuration::setRoomControlTopic(const char* roomControlTopic){
	strncpy(cd.roomControlTopic, roomControlTopic, CONFIG_ROOMCONTROL_TOPIC_LENGTH);
	update();  	
};

void Configuration::getServerTopic(char* serverTopic){
	strncpy(serverTopic, cd.serverTopic, CONFIG_SERVER_TOPIC_LENGTH);
};

void Configuration::setServerTopic(const char* serverTopic){
	strncpy(cd.serverTopic, serverTopic, CONFIG_SERVER_TOPIC_LENGTH);
	update();  	
};




ConfigurationData Configuration::cd;
byte Configuration::nullMAC[CONFIG_MAC_LENGTH] = {0x1e,0x00,0x00,0x00,0x00,0x02};
byte Configuration::nullIP[CONFIG_MQTT_SERVER_IP_LENGTH] = {192, 168, 0, 10};
