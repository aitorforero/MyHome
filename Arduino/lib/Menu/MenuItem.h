#ifndef _MenuItem_h
#define _MenuItem_h
#include <Arduino.h>

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
		int _x,_y,_width,_height;

		void initialize(const char* text, Image* icon);
		void onClick();
		

	public:
		MenuItem();
		MenuItem(const char* text);
		MenuItem(Image* icon);
		MenuItem(const char* text, Image* icon);

		Event<EventArgs>* click();
		void doClick();
		void setBounds( int x, int y, int width, int height);
		void draw(Adafruit_TFTLCD* TFT);
		void drawFocus(Adafruit_TFTLCD* TFT, uint16_t borderColor)

};

#endif