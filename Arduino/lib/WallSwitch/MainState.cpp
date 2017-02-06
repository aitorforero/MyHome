
#include "MainState.h"
#include <WallSwitch.h>
#include <Configuration.h>
#include <Debug.h>

MainState* MainState::Instance()
{
		static MainState   instance;
		return &instance;
};

void MainState::enter(WallSwitch* ws)
{
		Debug::debug("Enter in main state");

};

void MainState::execute(WallSwitch* ws)
{
  Debug::debug("Executing main state");

};

void MainState::exit(WallSwitch* ws)
{
  Debug::debug("Exiting from main state");

};
