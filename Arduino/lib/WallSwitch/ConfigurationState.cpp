#include "ConfigurationState.h"
#include <Event.h>
#include <EventArgs.h>
#include <WallSwitch.h>
#include <Configuration.h>
#include <FastDelegate.h>
#include <Debug.h>
#include <Menu.h>
#include <MenuItem.h>

using namespace fastdelegate;


ConfigurationState::ConfigurationState()
{
	configMenu = new Menu(0, 0, 320, 240, 3, 2);

	MACMenuItem = new MenuItem("MAC\n");
	configMenu->addItem(MACMenuItem);	
	MACMenuItem->click()->addHandler(MakeDelegate(this, &ConfigurationState::onMACMenuItemClick));

	MQTTMenuItem = new MenuItem("MQTT\n");
	configMenu->addItem(MQTTMenuItem);	
	MQTTMenuItem->click()->addHandler(MakeDelegate(this, &ConfigurationState::onMQTTMenuItemClick));

	zoneMenuItem = new MenuItem("Zone\n");
	configMenu->addItem(zoneMenuItem);	
	zoneMenuItem->click()->addHandler(MakeDelegate(this, &ConfigurationState::onZoneMenuItemClick));
};

ConfigurationState* ConfigurationState::Instance()
{
	static ConfigurationState   instance;
	return &instance;
};

void ConfigurationState::enter(WallSwitch* ws)
{
	configMenu->draw(ws->getTFT());
};

void ConfigurationState::execute(WallSwitch* ws)
{
	configMenu->doNext();
};

void ConfigurationState::exit(WallSwitch* ws)
{
	Debug::debug("Exiting from configuration state");
};

void ConfigurationState::onMACMenuItemClick(EventArgs* e)
{
	Serial.println("MAC Clicked");
};

void ConfigurationState::onMQTTMenuItemClick(EventArgs* e)
{
	Debug::debug("MQTT Clicked");
};

void ConfigurationState::onZoneMenuItemClick(EventArgs* e)
{
	Debug::debug("Zone Clicked");
};
