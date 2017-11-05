#ifndef ROOMCONTROLSTATE_H
#define ROOMCONTROLSTATE_H

#include <DebugUtils.h>
#include <State.h>
#include "ButtonEvents.h"

class RoomControl;		  
typedef FastDelegate1<ButtonEventArgs*, void> Handler;

class RoomControlState : public State<RoomControl>, ButtonEventsHandler
{
    private:
      Handler clickHndlr;
      Handler upHndlr;
      Handler downHndlr;

    protected:
      RoomControlState(): State<RoomControl>() {}; 

    public:
      virtual void enter(RoomControl* rc){
        DEBUG_PRINT("Enter");
        
        downHndlr = MakeDelegate(rc, &ButtonEventsHandler::handleButtonDown);
	      ((ButtonEventsController*)rc)->downEvent()->addHandler(MakeDelegate(rc, &ButtonEventsHandler::handleButtonDown));        
        ((ButtonEventsController*)rc)->clickEvent()->addHandler(MakeDelegate(rc, &ButtonEventsHandler::handleButtonClick));        
	      ((ButtonEventsController*)rc)->upEvent()->addHandler(MakeDelegate(rc, &ButtonEventsHandler::handleButtonUp));        
      };
      
      virtual State<RoomControl>* execute(RoomControl* rc){
        DEBUG_PRINT("Execute"); 
        return NULL;
      };
      
      virtual void exit(RoomControl* rc){
        DEBUG_PRINT("Exit");
        ((ButtonEventsController*)rc)->downEvent()->addHandler(MakeDelegate(rc, &ButtonEventsHandler::handleButtonDown));        
        ((ButtonEventsController*)rc)->clickEvent()->addHandler(MakeDelegate(rc, &ButtonEventsHandler::handleButtonClick));        
	      ((ButtonEventsController*)rc)->upEvent()->addHandler(MakeDelegate(rc, &ButtonEventsHandler::handleButtonUp));        
      };
};

#endif