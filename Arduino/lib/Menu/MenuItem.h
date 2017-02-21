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
	  bool focused;

	  void initialize(const char* text, Image* icon);
		void onClick();
	
	public:
		MenuItem();
		MenuItem(const char* text);
		MenuItem(Image* icon);
		MenuItem(const char* text, Image* icon);
	
		Event<EventArgs>* click();
	  void draw(Adafruit_TFTLCD* TFT, int x, int y);
};

#endif