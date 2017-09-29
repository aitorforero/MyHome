#include "ConfigurationEditNameState.h"
#include "Configuration.h"

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
	pos = 0;
	draw(rc);
};


void ConfigurationEditNameState::draw(RoomControl* rc)
{
	rc->u8g->firstPage();  
	do
	{
  		rc->u8g->setColorIndex(1); 
        rc->u8g->drawBox(0,0,128,16);
        rc->u8g->setFont(u8g_font_profont12r);
  		rc->u8g->setColorIndex(0); 
        rc->u8g->drawStr(2, 12, "Nombre");
  		rc->u8g->setColorIndex(1); 
        rc->u8g->setFont(u8g_font_profont22r);
		char* nameStr = Configuration::getName();
		int xPos = (128-rc->u8g->getStrWidth(nameStr)) / 2;
		rc->u8g->drawStr(xPos, 32, nameStr);
	} while(rc->u8g->nextPage());
};