
#include "MainState.h"
#include <RoomControl.h>
#include <Configuration.h>
#include <DebugUtils.h>

MainState* MainState::Instance()
{
	static MainState   instance;
	return &instance;
};

void MainState::enter(RoomControl* ws)
{
	DEBUG_PRINT("Enter in main state");
};

void MainState::execute(RoomControl* ws)
{
	DEBUG_PRINT("Executing main state");
};

void MainState::exit(RoomControl* ws)
{
	DEBUG_PRINT("Exiting from main state");
};
