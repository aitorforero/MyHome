#ifndef ROOMCONTROLSTATE_H
#define ROOMCONTROLSTATE_H

#include <DebugUtils.h>
#include <State.h> 
#include "RoomControlEventsController.h"

class RoomControl;		 

typedef FastDelegate1<ButtonEventArgs*, void> Handler;

class RoomControlState : public State<RoomControl>, public ButtonEventsHandler, public MQTTEventsHandler
{
	private:
		Event<ButtonEventArgs>::Handler clickHndlr;
		Event<ButtonEventArgs>::Handler upHndlr;
		Event<ButtonEventArgs>::Handler downHndlr;
		Event<MQTTMessageEventArgs>::Handler MQTTMessageHndlr;
  
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
 			RoomControlEventsController* ec = (RoomControlEventsController*)_owner;
			
			ec->downEvent()->removeHandler(downHndlr);
			ec->clickEvent()->removeHandler(clickHndlr);        
			ec->upEvent()->removeHandler(upHndlr);   
			ec->messageEvent()->removeHandler(MQTTMessageHndlr);   

			onSuspend();     
			
			DEBUG_PRINT("Suspended: " << getName())
		};

		void resume(){
			DEBUG_PRINT("Resuming: " << getName())

			downHndlr = MakeDelegate(this, &ButtonEventsHandler::handleButtonDown);
			clickHndlr = MakeDelegate(this, &ButtonEventsHandler::handleButtonClick);
			upHndlr = MakeDelegate(this, &ButtonEventsHandler::handleButtonUp);
			MQTTMessageHndlr = MakeDelegate(this, &MQTTEventsHandler::handleMQTTMessage);
			
 			RoomControlEventsController* ec = (RoomControlEventsController*)_owner;

			ec->messageEvent()->addHandler(MQTTMessageHndlr);  
			
			ec->downEvent()->addHandler(downHndlr);
			ec->clickEvent()->addHandler(clickHndlr);        
 			ec->upEvent()->addHandler(upHndlr); 
 			
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