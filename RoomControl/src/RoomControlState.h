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

		void execute(){
			onExecute();
		};

		void enter(){
			DEBUG_PRINT("Entering: " << getName())
			onEnter();
			DEBUG_PRINT("Entered: " << getName())
		};

		void exit(){
			DEBUG_PRINT("Exiting: " << getName())
			onExit();
			DEBUG_PRINT("Exited: " << getName())
		};
	  
		void suspend(){
			DEBUG_PRINT("Suspending: " << getName())
			((ButtonEventsController*)_owner)->downEvent()->removeHandler(downHndlr);
			((ButtonEventsController*)_owner)->clickEvent()->removeHandler(clickHndlr);        
			((ButtonEventsController*)_owner)->upEvent()->removeHandler(upHndlr);   

			onSuspend();     
			DEBUG_PRINT("Suspended: " << getName())
		};

		void resume(){
			DEBUG_PRINT("Resuming: " << getName())

			downHndlr = MakeDelegate(this, &ButtonEventsHandler::handleButtonDown);
			clickHndlr = MakeDelegate(this, &ButtonEventsHandler::handleButtonClick);
			upHndlr = MakeDelegate(this, &ButtonEventsHandler::handleButtonUp);
			
			((ButtonEventsController*)_owner)->downEvent()->addHandler(downHndlr);
			((ButtonEventsController*)_owner)->clickEvent()->addHandler(clickHndlr);        
			((ButtonEventsController*)_owner)->upEvent()->addHandler(upHndlr); 

			onResume();
			DEBUG_PRINT("Resumed: " << getName())
		};
	
	protected:
		virtual void onExecute(){};
		virtual void onEnter(){};
		virtual void onResume(){};
		virtual void onSuspend(){};
		virtual void onExit(){};

};

#endif