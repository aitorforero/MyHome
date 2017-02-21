#ifndef _ConfigurationState_h
#define _ConfigurationState_h

#include <State.h>
#include <WallSwitch.h>
#include <EventArgs.h>
#include <Menu.h>
#include <MenuItem.h>



class ConfigurationState : public State<WallSwitch>
{

private:
  Menu* configMenu;
  MenuItem* MACMenuItem;
  MenuItem* MQTTMenuItem;
  MenuItem* zoneMenuItem;
  ConfigurationState();
  void onMACMenuItemClick(EventArgs* e);
  void onMQTTMenuItemClick(EventArgs* e);
  void onZoneMenuItemClick(EventArgs* e);

public:
  static ConfigurationState* Instance();
  void enter(WallSwitch* ws);
  void execute(WallSwitch* ws);
  void exit(WallSwitch* ws);
};




#endif
