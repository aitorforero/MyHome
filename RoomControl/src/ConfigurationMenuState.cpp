#include <stdio.h>
#include <DebugUtils.h>
#include <IconCreate.h>
#include <IconPrevious.h>
#include <IconNext.h>
#include <IconDone.h>
#include <U8glib.h>
#define DEBUG
#include <DebugUtils.h>
#include "ConfigurationMenuState.h"
#include "ConfigurationEditNameState.h"
#include "Controls/Label.h"
#include "RoomControl.h"
#include "Configuration.h"
#include "Controls/HorizontalAlign.h"

ConfigurationMenuState::ConfigurationMenuState()
	: titleLabel(0, 0, 128, 16, "Configuracion"),
      optionNameLabel(0, 17, 128, 30, "d"),
      optionValueLabel(0, 54, 128, 16, "s")
{
    menuOptions[0]="Nombre";
    menuOptions[1]="MAC";
    menuOptions[2]="Servidor MQTT";
    menuOptions[3]="Puerto MQTT";
    menuOptions[4]="Salir";

    selectedOption = 0;
		
	titleLabel.setFont(u8g_font_profont12r);
    titleLabel.setBackColor(1);
    titleLabel.setForeColor(0);
    addChild(&titleLabel);
		  
	optionNameLabel.setFont(u8g_font_profont15r);
	optionNameLabel.setHorizontalAlign(center);
    addChild(&optionNameLabel);
		  
	optionValueLabel.setFont(u8g_font_profont12r);
	optionValueLabel.setHorizontalAlign(center);
    addChild(&optionValueLabel);
}



ConfigurationMenuState* ConfigurationMenuState::Instance()
{
	static ConfigurationMenuState   instance;
	return &instance;
};

void ConfigurationMenuState::enter(RoomControl* rc)
{
	rc->println("ConfigurationMenuState::enter");
    changeSelectedOption(rc, 0);
	drawMenu(rc);
};



void ConfigurationMenuState::drawMenu(RoomControl* rc)
{
	
	rc->u8g->firstPage();  
	do
	{
		drawChildren(rc->u8g);

		
		rc->u8g->setColorIndex(1); 
		rc->u8g->drawXBMP(2, 54, icon_previous_width, icon_previous_height, icon_previous_bits);
		if(selectedOption==(MENU_OPTION_COUNT - 1)) {
			rc->u8g->drawXBMP(59, 54, icon_done_width, icon_done_height, icon_done_bits);			
		} else {
			rc->u8g->drawXBMP(59, 54, icon_create_width, icon_create_height, icon_create_bits);			
		}

		rc->u8g->drawXBMP(116, 54, icon_next_width, icon_next_height, icon_next_bits);

	} while(rc->u8g->nextPage());

	//rc->println("OK");
};

void ConfigurationMenuState::changeSelectedOption(RoomControl* rc, int value){
	selectedOption += value;
	if(selectedOption < 0){
		selectedOption = MENU_OPTION_COUNT - 1;
	} else if(selectedOption >= MENU_OPTION_COUNT ) {
		selectedOption = 0;
	}
	

    optionNameLabel.setText(menuOptions[selectedOption]);

	char valueStr[18];
	switch(selectedOption) {
		case 0:
			sprintf(valueStr,"%s",Configuration::getName());
			break;
		case 1: 
			byte* mac;
			mac = Configuration::getMAC();
			sprintf(valueStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
			break;
		case 2:
			byte* IP;
			IP = Configuration::getMQTTServerIP();
			sprintf(valueStr, "%03d:%03d:%03d:%03d", IP[0], IP[1], IP[2], IP[3]);
			break;
		case 3:
			sprintf(valueStr, "%d", Configuration::getMQTTServerPort());
			break;
		case 4:
			sprintf(valueStr,"%s","");
			break;
	}
	
    optionValueLabel.setText(valueStr);


	drawMenu(rc);
}

void ConfigurationMenuState::onLeftButtonClick(RoomControl* rc){
	if(rc->rightButton->isPushed()) {
		this->onTwoButtonsClick(rc);
	} else {
		changeSelectedOption(rc, -1);
	} 
}

void ConfigurationMenuState::onRightButtonClick(RoomControl* rc){
	if(rc->leftButton->isPushed()) {
		this->onTwoButtonsClick(rc);
	} else	{
		changeSelectedOption(rc, 1);
	}
	

}

void ConfigurationMenuState::onTwoButtonsClick(RoomControl* rc){
	rc->changeState(ConfigurationEditNameState::Instance());
}