#ifndef _MenuItem_h
#define _MenuItem_h

#include <Adafruit_TFTLCD.h>

#include <Events.h>
#include <EventArgs.h>

class Image;

class MenuItem
{
	private:
		Image* icon;
		const char* text;
	  Event<EventArgs>* click;
	  void initialize(const char* text, Image* icon)
	
	protected:
		void onClick();
	
	public:
		MenuItem();
		MenuItem(const char* text);
		MenuItem(Imaentge* icon);
		MenuItem(const char* text, Image* icon);
	  void addClickHandler(EventHandler<TEventArgs>*);
	  void removeClickHandler(EventHandler<TEventArgs>*);
	  void draw(Adafruit_TFTLCD* TFT, int x, int y)
}

#endif