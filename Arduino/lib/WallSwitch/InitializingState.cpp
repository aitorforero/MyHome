#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <pin_magic.h>
#include <Adafruit_TFTLCD.h>
#include <RotaryEncoder.h>
#include "InitializingState.h"
#include "ConfigurationState.h"
#include <WallSwitch.h>
#include <Configuration.h>
#include "MainState.h"
#include <Debug.h>

InitializingState* InitializingState::Instance()
{
		static InitializingState   instance;
		return &instance;
};

void InitializingState::enter(WallSwitch* ws)
{
		// Read Configuration

};

void InitializingState::execute(WallSwitch* ws)
{

		Debug::debug("Initializing...");
		initializeButton(ws);
		initializeTFT(ws);
	  // let see splash screen
	  delay(2000);
		if(loadConfiguration())
		{
			ws->getStateMachine()->changeState(MainState::Instance());
		}
		else
		{
			ws->getStateMachine()->changeState(ConfigurationState::Instance());
		}

};

void InitializingState::exit(WallSwitch* ws)
{

};




void InitializingState::initializeTFT(WallSwitch* ws)
{
	Debug::debug("Initializing TFT...");
	Adafruit_TFTLCD*   mTFT = new Adafruit_TFTLCD(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
	ws->setTFT(mTFT);

	uint16_t identifier = mTFT->readID();
	mTFT->begin(identifier);
	mTFT->setRotation(1);
	mTFT->fillScreen(BLACK);
	mTFT->setTextColor(WHITE);
	mTFT->setTextSize(4);
	mTFT->setCursor(90, 50);
	mTFT->println("MyHome");
	mTFT->setCursor(25, 100);
	mTFT->println("Wall Switch");
	mTFT->setTextSize(1);
	mTFT->setCursor(110, 170);
	mTFT->println("by Aitor Forero");
 	//tft->drawXBitmap(0, 0, photo, photo_width,  photo_height, 0x00);
};

void InitializingState::initializeButton(WallSwitch* ws)
{  
  	Debug::debug("Initializing Button...");
	RotaryEncoder* mButton = new RotaryEncoder(A_PIN, B_PIN, SW_PIN);
	ws->setButton(mButton);
}

bool InitializingState::loadConfiguration()
{
  	Debug::debug("loading configuration...");
	return Configuration::load();
}
