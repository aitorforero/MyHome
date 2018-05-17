#include <DebugUtils.h>
#include <U8glib.h>
#include <ArduinoJson.h>

#include "MainState.h"
#include "RoomControl.h"
#include "Configuration.h"


MainState::MainState(RoomControl*  rc)
	: RoomControlState(rc),
	  nameLabel(0, 0, 128, 16, ""),
	  textLabel(0, 16, 128, 16, "")
{
	nameLabel.setFont(u8g_font_profont12r);
    nameLabel.setBackColor(1);
    nameLabel.setForeColor(0);
	nameLabel.setName("nameLabel");
    addChild(&nameLabel);
		 
	textLabel.setFont(u8g_font_profont15r);
	textLabel.setName("serverTextBox");
    addChild(&textLabel);
}

void MainState::draw(U8GLIB_SH1106_128X64 *u8g)
{
	u8g->firstPage();  
	do
	{
  		drawChildren(u8g);
	} while(u8g->nextPage());
};


const char * MainState::getName()
{
    return "MainState";
}


void MainState::execute() {
	bool connected  = true;

	if (!_owner->mqttClient->connected() && (millisLastAttempt == 0 || ((millis() - millisLastAttempt) >= 2000))) {
		DEBUG_PRINT("No conectado! Reintentando en 2s");
		millisLastAttempt = millis();
		connected = _owner->reconnect();
	}

	if (connected) {
		_owner->mqttClient->loop();
	}
}

void MainState::handleButtonClick(ButtonEventArgs* e){
	
};

void MainState::handleMQTTMessage(MQTTMessageEventArgs* e){
    DEBUG_PRINT("mqtt MESSAGE RECIBIDO")
	char message[e->getMessageLength()];
	e->getMessage(message);
    INFO_PRINT("Message arrived: " << message )


	StaticJsonBuffer<200> jsonBuffer;

	JsonObject& root = jsonBuffer.parseObject(message);



	MQTTState = root["state"];
	nameLabel.setText(root["name"]);
	textLabel.setText(root["text"]);

	draw(_owner->u8g);
};