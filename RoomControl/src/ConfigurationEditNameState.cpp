#include <IconCreate.h>
#include <IconPrevious.h>
#include <IconNext.h>
#include "ConfigurationEditNameState.h"
#include "Configuration.h"



ConfigurationEditNameState::ConfigurationEditNameState()
	: titleLabel(0, 0, 128, 16, "Nombre"),
	  menuButtonBar(0, 54, 128, 10),
	  moveLeftIcon(0,0, icon_previous_width, icon_previous_height, icon_previous_bits),
	  moveRightIcon(0,0, icon_next_width, icon_next_height, icon_next_bits),
	  selectIcon(0,0, icon_create_width, icon_create_height, icon_create_bits),	
      nameTextBox(0, 22, 128, 16, 8, &menuButtonBar)
{
	titleLabel.setFont(u8g_font_profont12r);
    titleLabel.setBackColor(1);
    titleLabel.setForeColor(0);
    addChild(&titleLabel);
		  
	nameTextBox.setFont(u8g_font_profont22r);
	nameTextBox.addCharacterRange(65, 90); // A..Z
    addChild(&nameTextBox);
	
	menuButtonBar.setLeftIcon(&moveLeftIcon);
	menuButtonBar.setRightIcon(&moveRightIcon);
	menuButtonBar.setCenterIcon(&selectIcon);
	menuButtonBar.setPadding(2, 0, 2, 0);
	addChild(&menuButtonBar);	  
}

void ConfigurationEditNameState::enter(RoomControl* rc)
{
    RoomControlState::enter(rc);
	nameTextBox.setValue(Configuration::getName());
	draw(rc->u8g);
};


void ConfigurationEditNameState::draw(U8GLIB_SH1106_128X64 *u8g)
{
	u8g->firstPage();  
	do
	{
  		drawChildren(u8g);
	} while(u8g->nextPage());
};

void ConfigurationEditNameState::handleButtonClick(ButtonEventArgs* e){
  //  RoomControl* rc = (RoomControl*)(e->getSender());
    
    switch(e->getButtonName()) {
        case rightButton:
	        nameTextBox.doRight();
            break;
        case leftButton:
	        nameTextBox.doLeft();
            break;
        case bothButtons:
	        nameTextBox.doSelect();
            break;
    };
};

