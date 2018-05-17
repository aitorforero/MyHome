#include <stdio.h>
#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <avr/wdt.h>
#include <DebugUtils.h>
#include <Button.h>
#include <EventArgs.h>
#include <Timer.h>
#include "InitializingState.h"
#include "RoomControl.h"
#include "Configuration.h"

#define MQTT_VERSION MQTT_VERSION_3_1_1

#define INVALID_VALUE -99

RoomControl::RoomControl() : 	ButtonEventsController(this), MQTTEventsController(this)
{
	line = 0;
	mStateMachine = new RoomControlStateMachine(this);
	mStateMachine->changeTo(new InitializingState(this));
};

RoomControl* RoomControl::Instance()
{
	static RoomControl instance;

	return &instance;
};


 
void RoomControl::loop() {
	Timer::loop();
	mStateMachine->update();
}


void RoomControl::changeToState(RoomControlState* s){
	mStateMachine->changeTo(s);
}

void RoomControl::moveToState(RoomControlState* s){
	mStateMachine->moveTo(s);	
}

void RoomControl::revertState(){
	mStateMachine->revert();	
}


void RoomControl::println(const char* text){
	INFO_PRINT(text)
	int i;
	u8g->setFont(u8g_font_profont10r);

	if (line==5) {
		for(i=0;i<4;i++){
			memcpy(buffer[i],buffer[i+1],81);
		}
		memcpy(buffer[4],text,81);
	} else {
		memcpy(buffer[line],text,81);
	}
	
	
	u8g->firstPage();  
	do
	{
		for(i=0;i<=line;i++){
			u8g->drawStr(2, (i+1)*12, buffer[i]);
		}
	} while(u8g->nextPage() );

	if (line<5) {
		line++;
	}	
}

void RoomControl::onLeftButtonClick(EventArgs* e){
  	if(this->rightButton->isPushed()) 
  	{
  		DEBUG_PRINT("Both after left Click!!")
		previousBothClick = true;
		onClick(ButtonName::bothButtons); 
	} 
	else if (!previousBothClick) 
	{
 		DEBUG_PRINT("Left Click!!")
		onClick(ButtonName::leftButton); 
  	}
	else
	{
  		DEBUG_PRINT("Previous Both Click!!")
		previousBothClick = false;
	}
}

void RoomControl::onRightButtonClick(EventArgs* e){
  	if(this->leftButton->isPushed()) 
  	{
  		DEBUG_PRINT("Both after right Click!!")
		previousBothClick = true;
		onClick(ButtonName::bothButtons); 
  	} 
  	else if (!previousBothClick) 
  	{
  		DEBUG_PRINT("Right Click!!")
		onClick(ButtonName::rightButton); 
	} 
	else
	{
  		DEBUG_PRINT("Previous Both Click!!")
		previousBothClick = false;
	}

}

void RoomControl::onLeftButtonDown(EventArgs* e){
  onDown(ButtonName::leftButton);   
}

void RoomControl::onRightButtonDown(EventArgs* e){
  onDown(ButtonName::rightButton);
}

void RoomControl::onLeftButtonUp(EventArgs* e){
  onUp(ButtonName::leftButton);
}

void RoomControl::onRightButtonUp(EventArgs* e){
  onUp(ButtonName::rightButton);
}

void RoomControl::reset(){
	wdt_enable(WDTO_60MS);
	while(1) {}
}

void RoomControl::onMQTTMessage(char* topic, byte* payload, unsigned int length) {
	char message[length+1] = {0};
	for(unsigned int i=0;i<length;i++)
		message[i] = payload[i];
	
	Instance()->onMessage(topic, message);
}

bool RoomControl::reconnect() {
    bool res;
    // Loop until we're reconnected
    println("Conectando con servidor MQTT...");
    // Attempt to connect
	char name[CONFIG_NAME_LENGTH];
	Configuration::getName(name);
	DEBUG_PRINT("Client ID" << name)

    if (mqttClient->connect(name)) {
      // Once connected, publish an announcement...
        println("Conectado!");
        // ... and resubscribe
		char rootTopic[CONFIG_ROOT_TOPIC_LENGTH];
		char roomControlTopic[CONFIG_ROOMCONTROL_TOPIC_LENGTH];
		byte MAC[CONFIG_MAC_LENGTH];
	
		Configuration::getMAC(MAC);
		Configuration::getRootTopic(rootTopic);
		Configuration::getRoomControlTopic(roomControlTopic);
		int topicLength = strlen(rootTopic) + strlen(roomControlTopic) + (CONFIG_MAC_LENGTH * 2) + 12;
		char subscribe_Topic[topicLength]; 
        sprintf(subscribe_Topic, "%s/%s/%02X%02X%02X%02X%02X%02X/setState", rootTopic, roomControlTopic, MAC[0],MAC[1],MAC[2],MAC[3],MAC[4],MAC[5]);
        mqttClient->subscribe(subscribe_Topic);
        println("Suscrito a: ");
        println(subscribe_Topic); 

        publishInitialize();

        res = true;
    } else {
		//char errorMessage[20]; 
        //sprintf(errorMessage, "Error!, rc= %", mqttClient.state());
        //println(errorMessage);
        res = false;
    }

	delay(1000);
    return res;
}


void RoomControl::publishCommand(const char* state, const char* item, const char* payload )
{
	// casa/mandos/command/{MAC}/{estado}/{item (left/right/both)}

	char rootTopic[CONFIG_ROOT_TOPIC_LENGTH];
	char roomControlTopic[CONFIG_ROOMCONTROL_TOPIC_LENGTH];
	byte MAC[CONFIG_MAC_LENGTH];

	Configuration::getMAC(MAC);
	Configuration::getRootTopic(rootTopic);
	Configuration::getRoomControlTopic(roomControlTopic);

	String topicString = String(rootTopic) + String("/");
	topicString += String(roomControlTopic) + String("/command/");
	topicString += String(MAC[0],16) + String(MAC[1],16) + String(MAC[2],16) + String(MAC[3],16) + String(MAC[4],16) + String(MAC[5],16) + String("/");
	topicString += String(state) + String("/");
	topicString += String(item);
	
	int topicLength = topicString.length()+1;

	char topic[topicLength];
	topicString.toCharArray(topic, topicLength); 

	mqttClient->publish(topic, payload);  
}

void RoomControl::publishInitialize()
{
	// casa/mandos/initialize}

	char rootTopic[CONFIG_ROOT_TOPIC_LENGTH];
	char roomControlTopic[CONFIG_ROOMCONTROL_TOPIC_LENGTH];
	byte MAC[CONFIG_MAC_LENGTH];

	Configuration::getMAC(MAC);
	Configuration::getRootTopic(rootTopic);
	Configuration::getRoomControlTopic(roomControlTopic);

	String topicString = String(rootTopic) + String("/");
	topicString += String(roomControlTopic) + String("/initialize");
	
	int topicLength = topicString.length()+1;
	char topic[topicLength];
	topicString.toCharArray(topic, topicLength); 

	char payload[13];
    sprintf(payload, "%02X%02X%02X%02X%02X%02X",  MAC[0],MAC[1],MAC[2],MAC[3],MAC[4],MAC[5]);

	mqttClient->publish(topic, payload);  
}