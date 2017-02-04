#ifndef _MainState_h
#define _MainState_h

#include <State.h>
#include <WallSwitch.h>
class MainState : public State<WallSwitch>
{
private:
  MainState(){};

public:
  static MainState* Instance();
  void enter(WallSwitch* ws);
  void execute(WallSwitch* ws);
  void exit(WallSwitch* ws);
};


#endif
