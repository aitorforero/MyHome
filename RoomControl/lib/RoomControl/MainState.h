#ifndef _MainState_h
#define _MainState_h

#include <State.h>
#include <RoomControl.h>
class MainState : public State<RoomControl>
{
    private:
      MainState(){};

    public:
      static MainState* Instance();
      void enter(RoomControl* ws);
      void execute(RoomControl* ws);
      void exit(RoomControl* ws);
};


#endif
