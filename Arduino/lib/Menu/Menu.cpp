#include "MenuItem.h"
#include "Menu.h"

Menu::Menu()
{
	menuItems = new List<MenuItem>;
};

void Menu::addItem(MenuItem* item)
{
	menuItems->add(item);
};

void Menu::removeItem(MenuItem* item)
{
	menuItems->remove(item);
};

void Menu:draw(Adafruit_TFTLCD* TFT, int x, int y)
{
	for(int i= 0; i<menuItems->count(); i++)
	{
		// TODO: Draw each in his place
		menuItems->items(i)->draw(TFT,x,y);
	}
}
