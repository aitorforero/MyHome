
#include <List.h>
#include "Menu.h"
#include "MenuItem.h"


Menu::Menu(int x, int y, int width, int heigh,int cols ,int rows)
{
	menuItems = new List<MenuItem*>;
	_x = x;
	_y = y;
	_width = width;
	_heigh = heigh;
	_cols = cols;
	_rows = rows;
};

void Menu::addItem(const MenuItem *item)
{
	menuItems->add(item);
};

void Menu::removeItem(const MenuItem *item)
{
	menuItems->remove(item);
};

void Menu::doClick()
{
	Debug::debug("Menu doClick");
	if(_focusedIndex > -1)
	{
		menuItems->item(_focusedIndex)->doClick();
	}
};


void Menu::draw(Adafruit_TFTLCD* TFT)
{
	if(menuItems->count() > 0)
	{
		_focusedIndex=0;
	}
	else
	{
		_focusedIndex = -1;
	}

	TFT->fillScreen(0x0);
	int col = 0;
	int row = 0;
	int x = 0;
	int y= 0;
	int colWidth = _width / _cols;
	int colHeight = _heigh / _rows;

	for(int i= 0; i<menuItems->count(); i++)
	{
		MenuItem* current = menuItems->item(i);
			
		
		uint16_t borderColor = (_focusedIndex == i) ? 0xFFFF : 0xCC00;
		x = colWidth * col;
		y = colHeight * row;
		
		current->draw(TFT, x, y, colWidth, colHeight, borderColor);
		
		col++;
		if(col==_cols)
		{
			row++;
			col=0;
		}
	}
};