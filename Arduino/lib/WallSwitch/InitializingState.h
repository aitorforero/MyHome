#ifndef _InitializingState_h
#define _InitializingState_h

#include <State.h>
#include <WallSwitch.h>

class InitializingState : public State<WallSwitch>
{
	private:
		InitializingState(){};

  public:
	  static InitializingState* Instance();
		void enter(WallSwitch* ws);
		void execute(WallSwitch* ws);
		void exit(WallSwitch* ws);
};

#endif