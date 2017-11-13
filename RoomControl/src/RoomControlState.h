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
  
	public:
		RoomControlState(RoomControl* rc):State<RoomControl>(rc){};

		virtual void enter(){
			INFO_PRINT("Entering...")
			downHndlr = MakeDelegate(this, &ButtonEventsHandler::handleButtonDown);
			clickHndlr = MakeDelegate(this, &ButtonEventsHandler::handleButtonClick);
			upHndlr = MakeDelegate(this, &ButtonEventsHandler::handleButtonUp);
 
			((ButtonEventsController*)_owner)->downEvent()->addHandler(downHndlr);        
			((ButtonEventsController*)_owner)->clickEvent()->addHandler(clickHndlr);        
			((ButtonEventsController*)_owner)->upEvent()->addHandler(upHndlr);        
			INFO_PRINT("Entered!")
		};
	  
	   virtual void execute(){};
	  
	  virtual void exit(){
		  INFO_PRINT("Exiting...")
		  ((ButtonEventsController*)_owner)->downEvent()->removeHandler(downHndlr);
		  ((ButtonEventsController*)_owner)->clickEvent()->removeHandler(clickHndlr);        
		  ((ButtonEventsController*)_owner)->upEvent()->removeHandler(upHndlr);        
		  INFO_PRINT("Exited!")
	  };
	  
	virtual void suspend(){};
	virtual void resume(){};

};

#endif