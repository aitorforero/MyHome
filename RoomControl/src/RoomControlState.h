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
		Event<ButtonEventArgs>::Handler clickHndlr;
		Event<ButtonEventArgs>::Handler upHndlr;
		Event<ButtonEventArgs>::Handler downHndlr;
  
	public:
		RoomControlState(RoomControl* rc):State<RoomControl>(rc){};



		virtual void enter(){
			downHndlr = MakeDelegate(this, &ButtonEventsHandler::handleButtonDown);
			clickHndlr = MakeDelegate(this, &ButtonEventsHandler::handleButtonClick);
			upHndlr = MakeDelegate(this, &ButtonEventsHandler::handleButtonUp);
			
			((ButtonEventsController*)_owner)->downEvent().addHandler(downHndlr);
			((ButtonEventsController*)_owner)->clickEvent().addHandler(clickHndlr);        
			((ButtonEventsController*)_owner)->upEvent().addHandler(upHndlr); 
		};
	  
	   virtual void execute(){
		   
	   };
	  
	  virtual void exit(){
		  ((ButtonEventsController*)_owner)->downEvent().removeHandler(downHndlr);
		  ((ButtonEventsController*)_owner)->clickEvent().removeHandler(clickHndlr);        
		  ((ButtonEventsController*)_owner)->upEvent().removeHandler(upHndlr);        
	  };
	  
	virtual void suspend(){};
	virtual void resume(){};

};

#endif