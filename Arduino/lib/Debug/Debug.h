#ifndef _Debug_h
#define _Debug_h


#include "Arduino.h"

class Debug
{
private:
  static bool initialized;

public:
  static void initialize(int br)
  {
    if(!initialized)
    {
      Serial.begin(br);
      initialized=true;
    }

  }

  static void debug(char* Text)
  {
    Serial.println(Text);
  }
};

#endif
