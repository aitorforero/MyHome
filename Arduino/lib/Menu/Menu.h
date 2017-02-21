#ifndef _Menu_h
#define _Menu_h


#include <List.h>
#include "MenuItem.h"

class Menu
{
	private:
		List<MenuItem>* menuItems;
		int _x; 
		int _y;
		int _width;
		int _heigh;
		int _cols;
		int _rows;
	
	public:
		Menu(int x, int y, int width, int heigh,int cols ,int rows);
		void addItem(const MenuItem& item);
		void removeItem(const MenuItem& item);
		void draw(Adafruit_TFTLCD* TFT);
};

#endif
