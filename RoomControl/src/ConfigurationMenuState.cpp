#include <ArduinoSTL.h>
#include <stdio.h>
#include <DebugUtils.h>
#include <IconCreate.h>
#include <IconPrevious.h>
#include <IconNext.h>
#include <IconDone.h>
#include <U8glib.h>
#include <DebugUtils.h>
#include "ConfigurationMenuState.h"
#include "ConfigurationEditNameState.h"
#include "ConfigurationEditMACState.h"
#include "ConfigurationEditServerState.h"
#include "ConfigurationEditPortState.h"
#include "MainState.h"
#include "RoomControl.h"
#include "Configuration.h"
#include "Controls/HorizontalAlign.h"


ConfigurationMenuState::ConfigurationMenuState(RoomControl*  rc)
	: RoomControlState(rc),
	  titleLabel(0, 0, 128, 16, "Configuracion"),
	  optionNameLabel(0, 16, 128, 19, ""), 
	  optionValueLabel(0, 35, 128, 16, ""),
	  moveLeftIcon(0,0, icon_previous_width, icon_previous_height, icon_previous_bits),
	  moveRightIcon(0,0, icon_next_width, icon_next_height, icon_next_bits),
	  selectIcon(0,0, icon_create_width, icon_create_height, icon_create_bits),		
	  menuButtonBar(0, 54, 128, 10)
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
	
	menuButtonBar.setLeftIcon(&moveLeftIcon);
	menuButtonBar.setRightIcon(&moveRightIcon);
	menuButtonBar.setCenterIcon(&selectIcon);
	menuButtonBar.setPadding(2, 0, 2, 0);
	addChild(&menuButtonBar);
}



void ConfigurationMenuState::onEnter()
{
	_owner->println("Entrando en modo configuracion...");
	changeSelectedOption(_owner->u8g, 0);
};

void ConfigurationMenuState::onExecute()
{
// 	_owner->println("Paso a editar el nombre directamente...");
// 	_owner->moveToState(new ConfigurationEditNameState(_owner));
};


void ConfigurationMenuState::onResume()
{
	changeSelectedOption(_owner->u8g, 0);
};


void ConfigurationMenuState::drawMenu(U8GLIB_SH1106_128X64 *u8g)
{
	u8g->firstPage();  
	do
	{
		drawChildren(u8g);
	} while(u8g->nextPage());
  
/*
	char xValue[24];
	sprintf(xValue, "%d %d %d %d %d %d",  moveRightIcon.getX(), moveRightIcon.getY(), moveRightIcon.getWidth(), moveRightIcon.getHeight());
	rc->println(xValue);
*/	
	
};

void ConfigurationMenuState::changeSelectedOption(U8GLIB_SH1106_128X64 *u8g, int value){
	selectedOption += value;
	if(selectedOption < 0){
		selectedOption = MENU_OPTION_COUNT - 1;
	} else if(selectedOption >= MENU_OPTION_COUNT ) {
		selectedOption = 0;
	}
	

	optionNameLabel.setText(menuOptions[selectedOption]);
	
	selectIcon.setBitmap(icon_create_width, icon_create_height, icon_create_bits);	
	char valueStr[18];
	switch(selectedOption) {
		case 0:
			Configuration::getName(valueStr);
			break;
		case 1: 
			byte mac[CONFIG_MAC_LENGTH];
			Configuration::getMAC(mac);
			sprintf(valueStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
			break;
		case 2:
			byte IP[CONFIG_MQTT_SERVER_IP_LENGTH];
			Configuration::getMQTTServerIP(IP);
			sprintf(valueStr, "%03d.%03d.%03d.%03d", IP[0], IP[1], IP[2], IP[3]);
			break;
		case 3:
			sprintf(valueStr, "%d", Configuration::getMQTTServerPort());
			break;
		case 4:
			selectIcon.setBitmap(icon_done_width, icon_done_height, icon_done_bits);	
			sprintf(valueStr,"%s","");
			break;
	}

	optionValueLabel.setText(valueStr);

	
	drawMenu(u8g);
}

void ConfigurationMenuState::handleButtonClick(ButtonEventArgs* e){
	DEBUG_PRINT("A ver donde me muevo");
	switch(e->getButtonName()) {
		case leftButton:
			changeSelectedOption(_owner->u8g, -1);
			break;
		case rightButton:
			changeSelectedOption(_owner->u8g, 1);
			break;
		default:
		 switch(selectedOption)
		 {
					case 0:
							_owner->moveToState(new ConfigurationEditNameState(_owner));
							break;
					case 1:
							_owner->moveToState(new ConfigurationEditMACState(_owner));					
							break;
					case 2:
							_owner->moveToState(new ConfigurationEditServerState(_owner));
							break;
					case 3:
							_owner->moveToState(new ConfigurationEditPortState(_owner));
							break;
					default:
							_owner->moveToState(new ConfigurationEditNameState(_owner));
							break;					
				}
			
			break;
	}
};

const char * ConfigurationMenuState::getName()
{
    return "ConfigurationMenuState";
};
