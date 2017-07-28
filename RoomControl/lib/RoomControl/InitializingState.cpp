#include <string.h>
#include "InitializingState.h"
#include "MainState.h"
#include <RoomControl.h>
#include <Configuration.h>
#include <DebugUtils.h>
#include <U8glib.h>
#include <SPI.h>
#include <Ethernet.h>




InitializingState* InitializingState::Instance()
{
	static InitializingState   instance;
	return &instance;
};

void InitializingState::enter(RoomControl* rc)
{
	DEBUG_PRINT("Enter in initializing state");
};

void InitializingState::execute(RoomControl* rc)
{
	DEBUG_PRINT("Executing initializing state");
	initializeScreen(rc);
	
	rc->println("Inicializando...");
	initializeEthernet(rc);	
	rc->println("Inicializado");
	
	
	
	rc->changeState(MainState::Instance());
};



void InitializingState::exit(RoomControl* rc)
{
	DEBUG_PRINT("Exiting from initializing state");
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
  Ethernet.begin(Configuration::mac);
  // Allow the hardware to sort itself out
  delay(1500);
  char IPAddress [16];
  sprintf(IPAddress,"%d.%d.%d.%d",Ethernet.localIP()[0],Ethernet.localIP()[1],Ethernet.localIP()[2],Ethernet.localIP()[3]);
	
  rc->println(IPAddress);
}

