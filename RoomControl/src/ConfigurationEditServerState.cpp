#include <ArduinoSTL.h>
#include <DebugUtils.h>
#include <IconCreate.h>
#include <IconPrevious.h>
#include <IconNext.h>
#include "ConfigurationEditServerState.h"
#include "Configuration.h"

const char * ConfigurationEditServerState::getName()
{
    return "ConfigurationEditServerState";
};

ConfigurationEditServerState::ConfigurationEditServerState(RoomControl*  rc)
	: RoomControlState(rc)
	, titleLabel(0, 0, 128, 16, "Servidor MQTT") 
	, menuButtonBar(0, 54, 128, 10)
	, moveLeftIcon(0,0, icon_previous_width, icon_previous_height, icon_previous_bits)
	, moveRightIcon(0,0, icon_next_width, icon_next_height, icon_next_bits)
	, selectIcon(0,0, icon_create_width, icon_create_height, icon_create_bits)	
    , serverTextBox(0, 22, 128, 16, (CONFIG_MQTT_SERVER_IP_LENGTH*4) - 1 , &menuButtonBar)
{
	titleLabel.setFont(u8g_font_profont12r);
    titleLabel.setBackColor(1);
    titleLabel.setForeColor(0);
	titleLabel.setName("titleLabel");
    addChild(&titleLabel);
		 
	serverTextBox.setFont(u8g_font_profont15r);
	serverTextBox.addCharacterRange(48, 57); // A..Z
	serverTextBox.addCharacterRange(46,46); // .
	serverTextBox.setName("serverTextBox");
    addChild(&serverTextBox);

	moveLeftIcon.setName("moveLeftIcon");
	moveRightIcon.setName("moveRightIcon");
	selectIcon.setName("selectIcon");
	
	menuButtonBar.setLeftIcon(&moveLeftIcon);
	menuButtonBar.setRightIcon(&moveRightIcon);
	menuButtonBar.setCenterIcon(&selectIcon);
	menuButtonBar.setPadding(2, 0, 2, 0);
	menuButtonBar.setName("menuButtonBar");
	addChild(&menuButtonBar);	  
}

void ConfigurationEditServerState::onEnter()
{
	byte *Server = new byte[CONFIG_MQTT_SERVER_IP_LENGTH];
	Configuration::getMQTTServerIP(Server);

	char *strServer = new char[CONFIG_MQTT_SERVER_IP_LENGTH*4];// Two digits for each byte,  '.' between and in the end '0'
	
	DEBUG_PRINT(Server[0] << " " << Server[1] << " " << Server[2] << " " << Server[3]);
	
	sprintf(strServer, "%03d.%03d.%03d.%03d", Server[0], Server[1], Server[2], Server[3]);
	strServer[CONFIG_MQTT_SERVER_IP_LENGTH*4-1] = 0;
	serverTextBox.setValue(strServer);

	delete strServer;
	delete Server;

	draw(_owner->u8g);
};


void ConfigurationEditServerState::onExit()
{
	// char *newName = new char[CONFIG_NAME_LENGTH+1];
	// Configuration::getName(newName);
	// serverTextBox.getValue(newName);

    // Configuration::setName(newName);
	// delete newName;
};

void ConfigurationEditServerState::draw(U8GLIB_SH1106_128X64 *u8g)
{
	u8g->firstPage();  
	do
	{
  		drawChildren(u8g);
	} while(u8g->nextPage());
};

void ConfigurationEditServerState::handleButtonClick(ButtonEventArgs* e){
	DEBUG_PRINT( "handleButtonClick: " << e->getButtonName() ) ;
    switch(e->getButtonName()) {
        case rightButton:
	        serverTextBox.doRight(_owner->u8g);
            break;
        case leftButton:
			DEBUG_PRINT("case leftButton") ;
	        serverTextBox.doLeft(_owner->u8g);
            break;
        default:
			if(serverTextBox.doSelect(_owner->u8g))
			{
				if(serverTextBox.saved())
				{
					char *Server= new byte[CONFIG_MQTT_SERVER_IP_LENGTH];
					Configuration::getMAC(Server);

					char *strServer = new char[CONFIG_MQTT_SERVER_IP_LENGTH*3]; // Two digits for each byte,  ':' between and in the end '0'
					serverTextBox.getValue(strServer);

					char strByte[3] = {0};
					for(int i = 0; i < CONFIG_MQTT_SERVER_IP_LENGTH; i++)
					{
						strncpy(strByte, strServer + (i * 3), 2);
						Server[i]=(byte)strtol(strByte, 0, 16);
					}

					Configuration::setMAC(Server);

					delete strServer;
					delete Server;
					}
            break;
			};
			draw(_owner->u8g);
	};
};

