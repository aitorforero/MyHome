#include <string.h>
#include <DebugUtils.h>
#include <U8glib.h>
#include <SPI.h>
#include <Ethernet.h>
#include <FastDelegate.h>
#include "InitializingState.h"
#include "ConfigurationMenuState.h"
#include "MainState.h"
#include "MainState.h"
#include "RoomControl.h"
#include "Configuration.h"


void InitializingState::execute()
{
	DEBUG_PRINT("Executing initializing state");
	initializeScreen();
	
	_owner->println("Inicializando...");
	initializeButtons();
	
	if(!Configuration::load()){
		_owner->println("Error en configuracion...");
		_owner->changeToState(new ConfigurationMenuState(_owner));
		return;
	}
	
	initializeEthernet();	
	_owner->println("Inicializado");
	
	_owner->changeToState(new MainState(_owner));
	
};

const char * InitializingState::getName()
{
    return "InitializingState";
};




void InitializingState::initializeScreen(){
	_owner->u8g = new U8GLIB_SH1106_128X64(U8G_I2C_OPT_NONE);
	
	switch (_owner->u8g->getMode()) {
		case U8G_MODE_R3G3B2:
			_owner->u8g->setColorIndex(255);     // White
			break;
		case U8G_MODE_GRAY2BIT:
    		_owner->u8g->setColorIndex(3);       // max intensity
			break;
		case U8G_MODE_BW:
    		_owner->u8g->setColorIndex(1);         // pixel on
			break;
		case U8G_MODE_HICOLOR:
    		_owner->u8g->setHiColorByRGB(255,255,255);
			break;
  	}
	
};

void InitializingState::initializeEthernet(){

	_owner->println("Inicializando ethernet...");
	_owner->ethClient = new EthernetClient;
	
	byte MAC[CONFIG_MAC_LENGTH];
	
	Configuration::getMAC(MAC);

	Ethernet.begin(MAC);
	// Allow the hardware to sort itself out
	delay(1500);
	char IPAddress [16];
	sprintf(IPAddress,"%d.%d.%d.%d",Ethernet.localIP()[0],Ethernet.localIP()[1],Ethernet.localIP()[2],Ethernet.localIP()[3]);

	_owner->println(IPAddress);
}

void InitializingState::initializeButtons() {  
 	_owner->println("Inicializando botones...");
	_owner->leftButton = new Button(A0 , LOW, true,MakeDelegate(_owner, &RoomControl::onLeftButtonClick), 10);
	_owner->leftButton->down()->addHandler(MakeDelegate(_owner, &RoomControl::onLeftButtonDown));
	_owner->leftButton->up()->addHandler(MakeDelegate(_owner, &RoomControl::onLeftButtonUp));
	_owner->rightButton = new Button(A1 , LOW, true, MakeDelegate(_owner, &RoomControl::onRightButtonClick), 10);
	_owner->rightButton->down()->addHandler(MakeDelegate(_owner, &RoomControl::onRightButtonDown));
	_owner->rightButton->up()->addHandler(MakeDelegate(_owner, &RoomControl::onRightButtonUp));
}
