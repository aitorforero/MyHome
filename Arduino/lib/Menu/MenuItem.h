#ifndef _MenuItem_h
#define _MenuItem_h

#include <Adafruit_TFTLCD.h>

#include <Event.h>
#include <EventArgs.h>

class Image;


class MenuItem
{
	private:
	  Image* icon;
	  const char* text;
	  Event<EventArgs>* _click;
	
	  void initialize(const char* text, Image* icon)
		{
			this->_click = new Event<EventArgs>;
 	        this->text = text;
			this->icon = icon;
		};
	
		void onClick()
		{
			EventArgs e = new EventArgs(this);
			this->click()->raise(&e);
		};
	
	public:
		MenuItem()
		{
			initialize(NULL,NULL);
		};
	
		MenuItem(const char* text)
		{
			initialize(text, NULL);
		};
	
		MenuItem(Image* icon)
		{
			initialize(NULL, icon);
		};

		MenuItem(const char* text, Image* icon)
		{
			initialize(text, icon);
		}
	
		Event<EventArgs>* click()
		{
			return this->_click;
		};
	
	
	  void draw(Adafruit_TFTLCD* TFT, int x, int y)
		{
			TFT->setCursor(x,y);
			TFT->println(text);
		};
};

#endif