#include <DebugUtils.h>
#include <U8glib.h>
#include <ArduinoJson.h>

#include "MainState.h"
#include "RoomControl.h"
#include "Configuration.h"


MainState::MainState(RoomControl*  rc)
	: RoomControlState(rc),
	  nameLabel(0, 0, 128, 16, ""),
	  textLabel(0, 22, 128, 16, "")
{
	nameLabel.setFont(u8g_font_profont12r);
    nameLabel.setBackColor(1);
    nameLabel.setForeColor(0);
	nameLabel.setName("nameLabel");
    addChild(&nameLabel);
		 
	textLabel.setFont(u8g_font_profont29r);
	textLabel.setName("textLabel");
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
	switch(e->getButtonName()) {
		case leftButton:
			_owner->publishCommand("left","click");
			break;
		case rightButton:
			_owner->publishCommand("right","click");
			break;
		default:
			_owner->publishCommand("both","click");
			break;
	}
};

void MainState::handleButtonDown(ButtonEventArgs* e){
	switch(e->getButtonName()) {
		case leftButton:
			_owner->publishCommand("left","down");
			break;
		case rightButton:
			_owner->publishCommand("right","down");
			break;
		default:
			_owner->publishCommand("both","down");
			break;
	}
};

void MainState::handleButtonUp(ButtonEventArgs* e){
	switch(e->getButtonName()) {
		case leftButton:
			_owner->publishCommand("left","up");
			break;
		case rightButton:
			_owner->publishCommand("right","up");
			break;
		default:
			_owner->publishCommand("both","up");
			break;
	}
};

void MainState::handleMQTTMessage(MQTTMessageEventArgs* e){
	char message[80] = {0};
	e->getMessage(message);



	StaticJsonBuffer<200> jsonBuffer;

	JsonObject& root = jsonBuffer.parseObject(message);

	const char* state = root["state"];
	const char* name = root["name"];
	const char* text = root["text"];

	_owner->setMQTTState(state);
	nameLabel.setText(name);
	textLabel.setText(text);
    DEBUG_PRINT(state)
    DEBUG_PRINT(name)
    DEBUG_PRINT(text)

 	draw(_owner->u8g);
};