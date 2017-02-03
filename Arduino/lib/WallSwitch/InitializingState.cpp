#include "InitializingState.h"
#include <WallSwitch.h>

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
	
};

void InitializingState::exit(WallSwitch* ws)
{
	
};