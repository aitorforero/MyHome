#include <ArduinoSTL.h>
#include <IconCreate.h>
#include <IconPrevious.h>
#include <IconNext.h>
#include "ConfigurationEditMACState.h"
#include "Configuration.h"

const char * ConfigurationEditMACState::getName()
{
    return "ConfigurationEditMACState";
};

ConfigurationEditMACState::ConfigurationEditMACState(RoomControl*  rc)
	: RoomControlState(rc)
	, titleLabel(0, 0, 128, 16, "MAC") 
	, menuButtonBar(0, 54, 128, 10)
	, moveLeftIcon(0,0, icon_previous_width, icon_previous_height, icon_previous_bits)
	, moveRightIcon(0,0, icon_next_width, icon_next_height, icon_next_bits)
	, selectIcon(0,0, icon_create_width, icon_create_height, icon_create_bits)	
    , MACTextBox(0, 22, 128, 16, 17, &menuButtonBar)
{
	titleLabel.setFont(u8g_font_profont12r);
    titleLabel.setBackColor(1);
    titleLabel.setForeColor(0);
	titleLabel.setName("titleLabel");
    addChild(&titleLabel);
		  
	MACTextBox.setFont(u8g_font_profont15r);
    MACTextBox.addCharacterRange(48, 57); // 0..9  
	MACTextBox.addCharacterRange(65, 70); // A..F
    MACTextBox.addCharacterRange(58, 58); //:

	MACTextBox.setName("MACTextBox");
    addChild(&MACTextBox);

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

void ConfigurationEditMACState::onEnter()
{
	byte *MAC = new byte[CONFIG_MAC_LENGTH];
	Configuration::getMAC(MAC);

	char *strMAC = new char[CONFIG_MAC_LENGTH*3]; // Two digits for each byte,  ':' between and in the end '0'
	sprintf(strMAC, "%02X:%02X:%02X:%02X:%02X:%02X", MAC[0], MAC[1], MAC[2], MAC[3], MAC[4], MAC[5]);
	MACTextBox.setValue(strMAC);

	delete strMAC;
	delete MAC;

	draw(_owner->u8g);
};


void ConfigurationEditMACState::onExit()
{
};

void ConfigurationEditMACState::draw(U8GLIB_SH1106_128X64 *u8g)
{
	u8g->firstPage();  
	do
	{
  		drawChildren(u8g);
	} while(u8g->nextPage());
};

void ConfigurationEditMACState::handleButtonClick(ButtonEventArgs* e){
	DEBUG_PRINT( "handleButtonClick: " << e->getButtonName() ) ;
    switch(e->getButtonName()) {
        case rightButton:
	        MACTextBox.doRight(_owner->u8g);
			draw(_owner->u8g);
            break;
        case leftButton:
	        MACTextBox.doLeft(_owner->u8g);
			draw(_owner->u8g);
            break;
		default:
			if(MACTextBox.doSelect(_owner->u8g))
			{
				if(MACTextBox.saved())
				{
					byte *MAC= new byte[CONFIG_MAC_LENGTH];
					Configuration::getMAC(MAC);

					char *strMAC = new char[CONFIG_MAC_LENGTH*3]; // Two digits for each byte,  ':' between and in the end '0'
					MACTextBox.getValue(strMAC);

					char strByte[3] = {0};
					for(int i = 0; i < CONFIG_MAC_LENGTH; i++)
					{
						strncpy(strByte, strMAC + (i * 3), 2);
						MAC[i]=(byte)strtol(strByte, 0, 16);
					}

					Configuration::setMAC(MAC);

					delete strMAC;
					delete MAC;
				}
				
				_owner->revertState();
			} else {
				draw(_owner->u8g);
			}

			         
			break;
        
    };
};

