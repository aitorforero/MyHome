#define   RED     0xF800
#define   GREEN   0x07E0
#define   WHITE   0xFFFF
#define   BLUE    0x001F
#define   CYAN    0x07FF
#define   YELLOW  0xFFE0
#define   MAGENTA 0xF81F
#define   BLACK   0x0000

#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <pin_magic.h>
#include <Adafruit_TFTLCD.h>
#include <StateMachine.h>
#include "InitializingState.h"
#include "WallSwitch.h"





WallSwitch::WallSwitch()
{

  mStateMachine = new StateMachine<WallSwitch>(this);
  mStateMachine->changeState(InitializingState::Instance());

};

WallSwitch* WallSwitch::Instance()
{
  static WallSwitch instance;

  return &instance;
};


void WallSwitch::update()
{
  mStateMachine->update();
};

void WallSwitch::initialize()
{
  Debug::debug("Initializing...");
  initializeTFT();
}


void WallSwitch::initializeTFT()
{
  Debug::debug("Initializing TFT...");
  mTFT = new Adafruit_TFTLCD(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
  mTFT->reset();

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
