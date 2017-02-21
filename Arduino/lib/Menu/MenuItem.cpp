#include <Adafruit_TFTLCD.h>
#include <Event.h>
#include <EventArgs.h>
#include "MenuItem.h"


void MenuItem::initialize(const char* text, Image* icon)
{
	this->_click = new Event<EventArgs>;
	this->text = text;
	this->icon = icon;
};

void MenuItem::onClick()
{
	EventArgs e = new EventArgs(this);
	this->click()->raise(&e);
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


void MenuItem::draw(Adafruit_TFTLCD* TFT, int x, int y)
{
	TFT->setCursor(x,y);
	TFT->println(text);
};
