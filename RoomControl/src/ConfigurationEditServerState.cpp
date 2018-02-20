#include <ArduinoSTL.h>
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
	, titleLabel(0, 0, 128, 16, "Nombre") 
	, menuButtonBar(0, 54, 128, 10)
	, moveLeftIcon(0,0, icon_previous_width, icon_previous_height, icon_previous_bits)
	, moveRightIcon(0,0, icon_next_width, icon_next_height, icon_next_bits)
	, selectIcon(0,0, icon_create_width, icon_create_height, icon_create_bits)	
    , serverTextBox(0, 22, 128, 16, 8, &menuButtonBar)
{
	titleLabel.setFont(u8g_font_profont12r);
    titleLabel.setBackColor(1);
    titleLabel.setForeColor(0);
	titleLabel.setName("titleLabel");
    addChild(&titleLabel);
		  
	DEBUG_PRINT("Añadiendo menuButtonBar...");
	serverTextBox.setFont(u8g_font_profont22r);
	serverTextBox.addCharacterRange(65, 90); // A..Z
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
	char *name= new char[CONFIG_NAME_LENGTH+1];
	Configuration::getName(name);
	serverTextBox.setValue(name);
	delete name;
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
	        serverTextBox.doSelect(_owner->u8g);
            break;
    };
	draw(_owner->u8g);
};

