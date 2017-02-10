
#include "ConfigurationState.h"
#include <WallSwitch.h>
#include <Configuration.h>
#include <Debug.h>

ConfigurationState* ConfigurationState::Instance()
{
		static ConfigurationState   instance;
		return &instance;
};

void ConfigurationState::enter(WallSwitch* ws)
{
		Debug::debug("Enter in configuration state");

};

void ConfigurationState::execute(WallSwitch* ws)
{
  Debug::debug("Executing configuration state");

};

void ConfigurationState::exit(WallSwitch* ws)
{
  Debug::debug("Exiting from configuration state");

};