
#include <List.h>
#include "Menu.h"
#include "MenuItem.h"

			Menu::Menu(int x, int y, int width, int heigh,int cols ,int rows)
		{
				menuItems = new List<MenuItem>;
				_x = x;
				_y = y;
				_width = width;
				_heigh = heigh;
				_cols = cols;
				_rows = rows;
		};

		void Menu::addItem(const MenuItem& item)
		{
				menuItems->add(item);
		};

		void Menu::removeItem(const MenuItem& item)
		{
				menuItems->remove(item);
		};


		void Menu::draw(Adafruit_TFTLCD* TFT)
		{
				int col = 0;
				int row = 0;
				int x = 0;
				int y= 0;
			
				for(int i= 0; i<menuItems->count(); i++)
				{
						x = _width / _cols * col;
					  y = _heigh / _rows ^ row;
					  menuItems->item(i).draw(TFT, x, y);
						col++;
						if(col==_cols)
						{
								row++;
								col=0;
						}
				}
			};