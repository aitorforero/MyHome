#include <Arduino.h>
#include <stdio.h>
#include "Debug.h"

void Debug::initialize(int br)
{
//#ifdef DEBUG
	Serial.begin(br);
	delay(1000);
//#endif
}

void Debug::debug(const char* text)
{
//#ifdef DEBUG
	int count = 1;
	while(text[count]!=0 || count<2000) count++; 
	Debug::debug(count, text);
//#endif
}

void Debug::debug(int maxSize, const char* text, ...)
{
//#ifdef DEBUG
	char buffer[maxSize];
	va_list args;
    va_start(args, text);

	snprintf(buffer, maxSize, text, args);
	
	Serial.println(buffer);
//#endif
};

