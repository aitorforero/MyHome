#define   RED     0xF800
#define   GREEN   0x07E0
#define   WHITE   0xFFFF
#define   BLUE    0x001F
#define   CYAN    0x07FF
#define   YELLOW  0xFFE0
#define   MAGENTA 0xF81F

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
  Serial.println("after");
  mStateMachine->changeState(InitializingState::Instance());
    Serial.println("after2");
};

WallSwitch* WallSwitch::Instance()
{
  static WallSwitch instance;

  return &instance;
};


void WallSwitch::update()
{
  Serial.println("WallSwitch::update");
  delay(5000);
  mStateMachine->update();
};

void WallSwitch::initializeTFT()
{
  mTFT = new Adafruit_TFTLCD(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
  mTFT->reset();

  uint16_t identifier = mTFT->readID();
  mTFT->begin(identifier);
  mTFT->setRotation(0);
  mTFT->fillScreen(RED);
  //tft->drawXBitmap(0, 0, photo, photo_width,  photo_height, 0x00);
};
