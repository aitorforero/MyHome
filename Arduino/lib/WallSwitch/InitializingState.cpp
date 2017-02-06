#include <Adafruit_GFX.h>    // Core graphics library
#include <pin_magic.h>
#include <Adafruit_TFTLCD.h>
#include "InitializingState.h"
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
		initializeTFT();
		loadConfiguration();

		ws->getStateMachine()->changeState(MainState::Instance());


		// TODO: Show splash screen
/*
	  // Try to load configuration
   if(Configuration::load())
	 {
    homeAutomation = new HomeAutomation(
      Configuration::getMACAddress(),
      Configuration::getServer().IPAddress,
      Configuration::getServer().port,
      IPAddress(
        Configuration::getIPAddress()[0],
        Configuration::getIPAddress()[1],
        Configuration::getIPAddress()[2],
        Configuration::getIPAddress()[3]));

    rotaryEncoder = new RotaryEncoder(A_PIN, B_PIN, SW_PIN);
	 }
	 else
	 {
	 }

*/


};

void InitializingState::exit(WallSwitch* ws)
{

};




void InitializingState::initializeTFT()
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

bool InitializingState::loadConfiguration()
{
  Debug::debug("loading configuration...");

}
