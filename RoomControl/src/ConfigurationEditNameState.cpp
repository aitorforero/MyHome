#include "ConfigurationEditNameState.h"

ConfigurationEditNameState::ConfigurationEditNameState(){
}



ConfigurationEditNameState* ConfigurationEditNameState::Instance()
{
	static ConfigurationEditNameState   instance;
	return &instance;
};

void ConfigurationEditNameState::enter(RoomControl* rc)
{
	DEBUG_PRINT("Enter in configuration edit name state");
	draw(rc);
};


void ConfigurationEditNameState::draw(RoomControl* rc)
{
	rc->u8g->firstPage();  
	do
	{
/*  		rc->u8g->setColorIndex(1); 
        rc->u8g->drawBox(0,0,128,16);
        rc->u8g->setFont(u8g_font_profont12);
  		rc->u8g->setColorIndex(0); 
        rc->u8g->drawStr(2, 12, "Configuracion");
  		rc->u8g->setColorIndex(1); 
        rc->u8g->setFont(u8g_font_profont15);
		int xPos = (128-rc->u8g->getStrWidth(menuOptions[selectedOption])) / 2;
		rc->u8g->drawStr(xPos, 32, menuOptions[selectedOption]);*/
	} while(rc->u8g->nextPage());
};