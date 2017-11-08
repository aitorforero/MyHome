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


 RoomControlState* InitializingState::execute(RoomControl* rc)
{
	DEBUG_PRINT("Executing initializing state");
	initializeScreen();
	
	rc->println("Inicializando...");
	initializeButtons();
	
	if(!Configuration::load()){
		return new ConfigurationMenuState();
	}
	
	initializeEthernet();	
	rc->println("Inicializado");
	
	rc->changeState(MainState::Instance());
	
	return NULL;
};




void InitializingState::initializeScreen(RoomControl* rc){
	rc->u8g = new U8GLIB_SH1106_128X64(U8G_I2C_OPT_NONE);
	
	switch (rc->u8g->getMode()) {
		case U8G_MODE_R3G3B2:
			rc->u8g->setColorIndex(255);     // White
			break;
		case U8G_MODE_GRAY2BIT:
    		rc->u8g->setColorIndex(3);       // max intensity
			break;
		case U8G_MODE_BW:
    		rc->u8g->setColorIndex(1);         // pixel on
			break;
		case U8G_MODE_HICOLOR:
    		rc->u8g->setHiColorByRGB(255,255,255);
			break;
  	}
	
};

void InitializingState::initializeEthernet(RoomControl* rc){

  rc->println("Inicializando ethernet...");
  rc->ethClient = new EthernetClient;
  Ethernet.begin(Configuration::getMAC());
  // Allow the hardware to sort itself out
  delay(1500);
  char IPAddress [16];
  sprintf(IPAddress,"%d.%d.%d.%d",Ethernet.localIP()[0],Ethernet.localIP()[1],Ethernet.localIP()[2],Ethernet.localIP()[3]);
	
  rc->println(IPAddress);
}

void InitializingState::initializeButtons(RoomControl* rc) {  
 	rc->println("Inicializando botones...");
	rc->leftButton = new Button(A0 , LOW, true,MakeDelegate(rc, &RoomControl::onLeftButtonClick), 10);
	rc->leftButton->down()->addHandler(MakeDelegate(rc, &RoomControl::onLeftButtonDown));
	rc->leftButton->up()->addHandler(MakeDelegate(rc, &RoomControl::onLeftButtonUp));
	rc->rightButton = new Button(A1 , LOW, true, MakeDelegate(rc, &RoomControl::onRightButtonClick), 10);
	rc->rightButton->down()->addHandler(MakeDelegate(rc, &RoomControl::onRightButtonDown));
	rc->rightButton->up()->addHandler(MakeDelegate(rc, &RoomControl::onRightButtonUp));
}
