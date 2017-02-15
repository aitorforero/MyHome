#ifndef _Menu_h
#define _Menu_h

#include <List.h>
#include "MenuItem.h"

class Menu
{
	private:
		List<MenuItem> menuItems;
	public:
		Menu();
		void addItem(MenuItem* item);
		void removeItem(MenuItem* item);
	  void draw(#include <Adafruit_TFTLCD.h>int x, int y)
}

#endif
