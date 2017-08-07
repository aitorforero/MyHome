#include <DebugUtils.h>
#include "ConfigurationMenuState.h"
#include "RoomControl.h"
#include "Configuration.h"

ConfigurationMenuState::ConfigurationMenuState(){
    menuOptions[0]="MAC";
    menuOptions[1]="Salir";
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
};

void ConfigurationMenuState::execute(RoomControl* rc)
{
	DEBUG_PRINT("Executing configuration menu state");
    drawMenu(rc);
};

void ConfigurationMenuState::exit(RoomControl* rc)
{
	DEBUG_PRINT("Exiting from configuration menu state");
};


void ConfigurationMenuState::drawMenu(RoomControl* rc)
{
	rc->u8g->firstPage();  
	do
	{
  		rc->u8g->setColorIndex(1); 
        rc->u8g->drawBox(0,0,128,16);
        rc->u8g->setFont(u8g_font_profont12);
  		rc->u8g->setColorIndex(0); 
        rc->u8g->drawStr(2, 12, "Configuracion");
  		rc->u8g->setColorIndex(1); 
        rc->u8g->setFont(u8g_font_profont10);
        rc->u8g->drawStr(2, 62, ">");
        rc->u8g->drawStr(100, 62, "Sel");
		
        rc->u8g->setFont(u8g_font_profont12);
		rc->u8g->drawStr(2,40, menuOptions[selectedOption]);
	} while(rc->u8g->nextPage() );

    
};

void ConfigurationMenuState::onLeftButtonClick(RoomControl* rc){
	selectedOption++;
	if(selectedOption==MENU_OPTION_COUNT) {
		selectedOption = 0;
	}
}

void ConfigurationMenuState::onRightButtonClick(RoomControl* rc){
}