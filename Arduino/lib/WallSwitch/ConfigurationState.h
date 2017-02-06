#ifndef _ConfigurationState_h
#define _ConfigurationState_h

#include <State.h>
#include <WallSwitch.h>
class ConfigurationState : public State<WallSwitch>
{
private:
  ConfigurationState(){};

public:
  static ConfigurationState* Instance();
  void enter(WallSwitch* ws);
  void execute(WallSwitch* ws);
  void exit(WallSwitch* ws);
};


#endif
