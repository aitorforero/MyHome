#ifndef _Debug_h
#define _Debug_h


#include "Arduino.h"

class Debug
{
public:
  static void initialize(int br)
  {
      Serial.begin(br);
      delay(1000);
  }

  static void debug(char* Text)
  {
    Serial.println(Text);
  }
};

#endif
