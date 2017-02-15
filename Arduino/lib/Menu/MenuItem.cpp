#Include <Event.h>
#Include <EventArgs.h>
#Include "MenuItem.h"



void MenuItem::onClick()
{
	EventArgs e = new EventArgs(this);
	this->click->raise(e);
};
	
MenuItem::MenuItem()
{
	initialize(NULL,NULL);
	
};
MenuItem::MenuItem(const char* text)
{
	initialize(text, NULL);
};

MenuItem::MenuItem(Imaentge* icon)
{
	initialize(NULL, icon);
};

MenuItem::MenuItem(const char* text, Image* icon)
{
	initialize(text, icon);
}

MenuItem::Initialize(const char* text, Image* icon)
{
	this-click = new Event<EventArgs>;
	this->text = text;
	this->icon = icon;
};

void MenuItem::addClickHandler(EventHandler<TEventArgs>* handler)
{
	this->click->addHandler(handler);
	
};

void MenuItem::removeClickHandler(EventHandler<TEventArgs>* handler)
{
	this-click->removeHandler(handler);
};

void MenuItem::draw(Adafruit_TFTLCD* TFT, int x, int y)
{
	// TODO: Draw itself
}