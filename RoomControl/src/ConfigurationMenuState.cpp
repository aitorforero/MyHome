#include <stdio.h>
#include <DebugUtils.h>
#include <IconCreate.h>
#include <IconPrevious.h>
#include <IconNext.h>
#include <IconDone.h>
#include "ConfigurationMenuState.h"
#include "ConfigurationEditNameState.h"
#include "Controls/Label.h"
#include "RoomControl.h"
#include "Configuration.h"

ConfigurationMenuState::ConfigurationMenuState():Title(0, 0, 128, 16, "Configuracion"){
    menuOptions[0]="Nombre";
    menuOptions[1]="MAC";
    menuOptions[2]="Servidor MQTT";
    menuOptions[3]="Puerto MQTT";
    menuOptions[4]="Salir";
	
		
    getChildControls()->add(Title);
}



ConfigurationMenuState* ConfigurationMenuState::Instance()
{
	static ConfigurationMenuState   instance;
	return &instance;
};

void ConfigurationMenuState::enter(RoomControl* rc)
{
	DEBUG_PRINT("Enter in configuration menu state");
    selectedOption = 0;
	drawMenu(rc);
};



void ConfigurationMenuState::drawMenu(RoomControl* rc)
{
	rc->u8g->firstPage();  
	do
	{
		drawChildren(rc->u8g);
  		rc->u8g->setColorIndex(1); 
        rc->u8g->setFont(u8g_font_profont15r);
		int xPos = (128-rc->u8g->getStrWidth(menuOptions[selectedOption])) / 2;
		rc->u8g->drawStr(xPos, 32, menuOptions[selectedOption]);
        rc->u8g->setFont(u8g_font_profont12r);
		switch(selectedOption) {
			case 0:
				char* nameStr;
				nameStr = Configuration::getName();
				xPos = (128-rc->u8g->getStrWidth(nameStr)) / 2;
				rc->u8g->drawStr(xPos, 48, nameStr);
				break;
			case 1: 
				byte* mac;
				mac = Configuration::getMAC();
				char macStr[18];
				sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
				xPos = (128-rc->u8g->getStrWidth(macStr)) / 2;
				rc->u8g->drawStr(xPos, 48, macStr);
				break;
			case 2:
				byte* IP;
				IP = Configuration::getMQTTServerIP();
				char ipStr[16];
				sprintf(ipStr, "%03d:%03d:%03d:%03d", IP[0], IP[1], IP[2], IP[3]);
				xPos = (128-rc->u8g->getStrWidth(ipStr)) / 2;
				rc->u8g->drawStr(xPos, 48, ipStr);
				break;
			case 3:
				char portStr[6];
				sprintf(portStr, "%d", Configuration::getMQTTServerPort());
				xPos = (128-rc->u8g->getStrWidth(portStr)) / 2;
				rc->u8g->drawStr(xPos, 48, portStr);
				break;
			case 4:
				break;
		}
		rc->u8g->drawXBMP(2, 54, icon_previous_width, icon_previous_height, icon_previous_bits);
		if(selectedOption==(MENU_OPTION_COUNT - 1)) {
			rc->u8g->drawXBMP(59, 54, icon_done_width, icon_done_height, icon_done_bits);			
		} else {
			rc->u8g->drawXBMP(59, 54, icon_create_width, icon_create_height, icon_create_bits);			
		}

		rc->u8g->drawXBMP(116, 54, icon_next_width, icon_next_height, icon_next_bits);

	} while(rc->u8g->nextPage());
};



void ConfigurationMenuState::onLeftButtonClick(RoomControl* rc){
	if(rc->rightButton->isPushed()) {
		this->onTwoButtonsClick(rc);
	} else {
		if(selectedOption>0){
			selectedOption--;
		} else {
			selectedOption = MENU_OPTION_COUNT - 1;
		}
		drawMenu(rc);
	}
  
}

void ConfigurationMenuState::onRightButtonClick(RoomControl* rc){
	if(rc->leftButton->isPushed()) {
		this->onTwoButtonsClick(rc);
	} else	{
		if(selectedOption < MENU_OPTION_COUNT - 1) {
			selectedOption++;
		} else {
			selectedOption = 0;
		}
		drawMenu(rc);
	}
	

}

void ConfigurationMenuState::onTwoButtonsClick(RoomControl* rc){
	rc->changeState(ConfigurationEditNameState::Instance());
}