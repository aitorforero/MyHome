#include <Adafruit_TFTLCD.h>
#include <Event.h>
#include <EventArgs.h>
#include "MenuItem.h"
#include <Debug.h>

#define MENUITEM_PADDING 6
#define MENUITEM_IMAGE_TEXT_PROPORTION 5


void MenuItem::initialize(const char* text, Image* icon)
{
	this->_click = new Event<EventArgs>;
	this->text = text;
	this->icon = icon;
	this->setBounds(0,0,0,0);
};

void MenuItem::onClick()
{
	EventArgs e = new EventArgs(this);
	this->click()->raise(&e);
};

void MenuItem::doClick()
{
	onClick();
};


MenuItem::MenuItem()
{
	initialize(NULL,NULL);
};

MenuItem::MenuItem(const char* text)
{
	initialize(text, NULL);
};

MenuItem::MenuItem(Image* icon)
{
	initialize(NULL, icon);
};

MenuItem::MenuItem(const char* text, Image* icon)
{
	initialize(text, icon);
};

Event<EventArgs>* MenuItem::click()
{
	return this->_click;
};


void MenuItem::draw(Adafruit_TFTLCD* TFT)
{
	int left = _x + MENUITEM_PADDING;
	int top = _y + MENUITEM_PADDING;
	int contentWidth = _width - MENUITEM_PADDING * 2;
	int heightUnity = (_height - MENUITEM_PADDING * 3) / (MENUITEM_IMAGE_TEXT_PROPORTION + 1) ;
	int textTop = y + _height - MENUITEM_PADDING - heightUnity;
	
	TFT->fillRect(left, top, contentWidth, heightUnity * MENUITEM_IMAGE_TEXT_PROPORTION, 0xFFFF);
	
	// Draw textTop
	int16_t  x1, y1;
	uint16_t w, h;
 	TFT->getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
	
	TFT->setCursor(left + (contentWidth-w) / 2 , textTop + (heightUnity - h) / 2 );
	TFT->println(text);
};

void MenuItem::drawFocus(Adafruit_TFTLCD* TFT, uint16_t borderColor)
{
	TFT->drawRect(_x, _y, _width, _height, borderColor);
};

void  MenuItem::setBounds( int x, int y, int width, int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
}


