#ifndef _Menu_h
#define _Menu_h


#include <List.h>
#include "MenuItem.h"

class Menu
{
   // typedef etl::vector<MenuItem*, 10> MenuItemCollection;

	private:
		List<MenuItem>* menuItems;
	public:
		Menu()
		{
//			menuItems = new MenuItemCollection;
		};

		void addItem(MenuItem* item)
		{
//			menuItems->push_back(item);
		};

		void removeItem(MenuItem* item)
		{
		//	menuItems->remove(item);
		};


		void draw(Adafruit_TFTLCD* TFT, int x, int y)
		{
			for(int i= 0; i<menuItems->count(); i++)
			{
				// TODO: Draw each in his place
	//			menuItems->item(i)->draw(TFT,x,y);
			}
		};

};

#endif
