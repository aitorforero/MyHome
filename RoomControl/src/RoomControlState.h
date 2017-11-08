#ifndef ROOMCONTROLSTATE_H
#define ROOMCONTROLSTATE_H

#include <DebugUtils.h>
#include <State.h>
#include "ButtonEvents.h"

class RoomControl;		  
typedef FastDelegate1<ButtonEventArgs*, void> Handler;

class RoomControlState : public State<RoomControl>, public ButtonEventsHandler
{
    private:
        Handler clickHndlr;
        Handler upHndlr;
        Handler downHndlr;

    protected:
        RoomControlState(){};
  
    public:
        virtual void enter(RoomControl* rc){
            downHndlr = MakeDelegate(this, &ButtonEventsHandler::handleButtonDown);
            clickHndlr = MakeDelegate(this, &ButtonEventsHandler::handleButtonClick);
            upHndlr = MakeDelegate(this, &ButtonEventsHandler::handleButtonUp);
 
            ((ButtonEventsController*)rc)->downEvent()->addHandler(downHndlr);        
            ((ButtonEventsController*)rc)->clickEvent()->addHandler(clickHndlr);        
            ((ButtonEventsController*)rc)->upEvent()->addHandler(upHndlr);        
        };
      
       virtual State<RoomControl>* execute(RoomControl* rc){
            return NULL;
        };
      
      virtual void exit(RoomControl* rc){
            ((ButtonEventsController*)rc)->downEvent()->removeHandler(downHndlr);        
            ((ButtonEventsController*)rc)->clickEvent()->removeHandler(clickHndlr);        
            ((ButtonEventsController*)rc)->upEvent()->removeHandler(upHndlr);        
      };
      
     virtual void suspend(RoomControl* rc){};
    virtual void resume(RoomControl* rc){};

};

#endif