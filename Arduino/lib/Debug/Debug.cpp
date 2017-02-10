#include <Arduino.h>
#include <stdio.h>
#include "Debug.h"

void Debug::initialize(int br)
{
	Serial.begin(br);
	delay(1000);
}

void Debug::debug(const char* text)
{
	Debug::debug(sizeof(text),text);
}

void Debug::debug(int maxSize,const char* text, ...)
{
	char buffer[maxSize];
	va_list args;
    va_start(args, text);

	snprintf(buffer, maxSize, text, args);
	
	Serial.println(buffer);
};

