#ifndef ROOMCONTROLSTATE_H
#define ROOMCONTROLSTATE_H

#include <DebugUtils.h>
#include <State.h> 
#include "ButtonEvents.h"
#include "MQTTEvents.h"

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
			MQTTEventsController* mqttEC = _owner;
			ButtonEventsController* bEC = _owner;			
			bEC->downEvent()->removeHandler(downHndlr);
			bEC->clickEvent()->removeHandler(clickHndlr);        
			bEC->upEvent()->removeHandler(upHndlr);   
			mqttEC->messageEvent()->removeHandler(MQTTMessageHndlr);   

			onSuspend();     
			DEBUG_PRINT("Suspended: " << getName())
		};

		void resume(){
			DEBUG_PRINT("Resuming: " << getName())

			downHndlr = MakeDelegate(this, &ButtonEventsHandler::handleButtonDown);
			clickHndlr = MakeDelegate(this, &ButtonEventsHandler::handleButtonClick);
			upHndlr = MakeDelegate(this, &ButtonEventsHandler::handleButtonUp);
			MQTTMessageHndlr = MakeDelegate(this, &MQTTEventsHandler::handleMQTTMessage);
			
 			MQTTEventsController* mqttEC = _owner;
			ButtonEventsController* bEC = _owner;			

            DEBUG_PRINT(mqttEC->messageEvent())
           	DEBUG_PRINT(bEC->downEvent())
           	DEBUG_PRINT(bEC->clickEvent())
           	DEBUG_PRINT(bEC->upEvent())


          	DEBUG_PRINT("Anadir " << mqttEC->messageEvent())
			mqttEC->messageEvent()->addHandler(MQTTMessageHndlr);  
            DEBUG_PRINT("Anadido " << mqttEC->messageEvent()->handlerCount())
			
			bEC->downEvent()->addHandler(downHndlr);
			bEC->clickEvent()->addHandler(clickHndlr);        
            DEBUG_PRINT("Anadir " << bEC->upEvent()->handlerCount())
			bEC->upEvent()->addHandler(upHndlr); 
             DEBUG_PRINT("Anadir " << bEC->upEvent()->handlerCount())
			
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