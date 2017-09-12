#include <DebugUtils.h>

#include "MainState.h"
#include "RoomControl.h"
#include "Configuration.h"

MainState* MainState::Instance()
{
	static MainState   instance;
	return &instance;
};



