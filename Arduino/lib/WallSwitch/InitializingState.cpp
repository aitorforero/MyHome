#include "InitializingState.h"
#include <WallSwitch.h>
#include <Configuration.h>
#include "MainState.h"
#include <Debug.h>

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

		ws->initialize();

		ws->getStateMachine()->changeState(MainState::Instance());


		// TODO: Show splash screen
/*
	  // Try to load configuration
   if(Configuration::load())
	 {
    homeAutomation = new HomeAutomation(
      Configuration::getMACAddress(),
      Configuration::getServer().IPAddress,
      Configuration::getServer().port,
      IPAddress(
        Configuration::getIPAddress()[0],
        Configuration::getIPAddress()[1],
        Configuration::getIPAddress()[2],
        Configuration::getIPAddress()[3]));

    rotaryEncoder = new RotaryEncoder(A_PIN, B_PIN, SW_PIN);
	 }
	 else
	 {
	 }

*/


};

void InitializingState::exit(WallSwitch* ws)
{

};
