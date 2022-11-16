#include <ArduinoSTL.h>
#include <IconCreate.h>
#include <IconPrevious.h>
#include <IconNext.h>
#include "ConfigurationEditPortState.h"
#include "Configuration.h"

const char * ConfigurationEditPortState::getName()
{
    return "ConfigurationEditPortState";
};

ConfigurationEditPortState::ConfigurationEditPortState(RoomControl*  rc)
	: RoomControlState(rc)
	, titleLabel(0, 0, 128, 16, "Nombre") 
	, menuButtonBar(0, 54, 128, 10)
	, moveLeftIcon(0,0, icon_previous_width, icon_previous_height, icon_previous_bits)
	, moveRightIcon(0,0, icon_next_width, icon_next_height, icon_next_bits)
	, selectIcon(0,0, icon_create_width, icon_create_height, icon_create_bits)	
    , portTextBox(0, 22, 128, 16, 8, &menuButtonBar)
{
	titleLabel.setFont(u8g_font_profont12r);
    titleLabel.setBackColor(1);
    titleLabel.setForeColor(0);
	titleLabel.setName("titleLabel");
    addChild(&titleLabel);
		  
	DEBUG_PRINT("Añadiendo menuButtonBar...");
	portTextBox.setFont(u8g_font_profont22r);
	portTextBox.addCharacterRange(48, 57); // 0..9
	portTextBox.setName("portTextBox");
    addChild(&portTextBox);

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

void ConfigurationEditPortState::onEnter()
{
	char *name= new char[CONFIG_NAME_LENGTH+1];
	Configuration::getName(name);
	portTextBox.setValue(name);
	delete name;
	draw(_owner->u8g);
};


void ConfigurationEditPortState::onExit()
{
	// char *newName = new char[CONFIG_NAME_LENGTH+1];
	// Configuration::getName(newName);
	// portTextBox.getValue(newName);

    // Configuration::setName(newName);
	// delete newName;
};

void ConfigurationEditPortState::draw(U8GLIB_SH1106_128X64 *u8g)
{
	u8g->firstPage();  
	do
	{
  		drawChildren(u8g);
	} while(u8g->nextPage());
};

void ConfigurationEditPortState::handleButtonClick(ButtonEventArgs* e){
	DEBUG_PRINT( "handleButtonClick: " << e->getButtonName() ) ;
    switch(e->getButtonName()) {
        case rightButton:
	        portTextBox.doRight(_owner->u8g);
			draw(_owner->u8g);
            break;
        case leftButton:
			DEBUG_PRINT("case leftButton") ;
	        portTextBox.doLeft(_owner->u8g);
			draw(_owner->u8g);
            break;
        default:
	        if (portTextBox.doSelect(_owner->u8g)) {
				if(portTextBox.saved())
				{
					int port;
	
					char *strPort = new char[8]; 
					portTextBox.getValue(strPort);
					port=(int)strtol(strPort, 0, 10);

					Configuration::setMQTTServerPort(port);

					delete strPort;
				}
				
				_owner->revertState();

			} else {
				draw(_owner->u8g);
			}
            break;
    };

};

