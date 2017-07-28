#ifndef _InitializingState_h
#define _InitializingState_h

#include <State.h>
#include <RoomControl.h>
class InitializingState : public State<RoomControl>
{
    private:
      InitializingState(){};
      void initializeScreen(RoomControl* rc);
      void initializeEthernet(RoomControl* rc);
      
    public:
      static InitializingState* Instance();
      void enter(RoomControl* rc);
      void execute(RoomControl* rc);
      void exit(RoomControl* rc);
};


#endif