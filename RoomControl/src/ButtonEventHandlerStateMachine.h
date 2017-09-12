#ifndef BUTTONEVENTHANDLERSTATEMACHINE_H
#define BUTTONEVENTHANDLERSTATEMACHINE_H

#include <StateMachine.h>
#include <DebugUtils.h>
#include "ButtonEventHandler.h"



template <class t> class ButtonEventHandlerStateMachine : public StateMachine<t>, public ButtonEventHandler<t>
{
    public:
        ButtonEventHandlerStateMachine(t* owner):StateMachine<t>(owner) {} ;



        void onLeftButtonClick(t* rc){
            ((ButtonEventHandlerState<t>*)this->_CurrentState)->onLeftButtonClick(rc);
        };
        
        void onRightButtonClick(t* rc){
            ((ButtonEventHandlerState<t>*)this->_CurrentState)->onRightButtonClick(rc);
        };
        
        void onLeftButtonDown(t* rc){
            ((ButtonEventHandlerState<t>*)this->_CurrentState)->onLeftButtonDown(rc);
        };
        
        void onRightButtonDown(t* rc){
            ((ButtonEventHandlerState<t>*)this->_CurrentState)->onRightButtonDown(rc);
        };

        void onLeftButtonUp(t* rc){
            ((ButtonEventHandlerState<t>*)this->_CurrentState)->onLeftButtonUp(rc);
        };
        
        void onRightButtonUp(t* rc){
            ((ButtonEventHandlerState<t>*)this->_CurrentState)->onRightButtonUp(rc);
        };

};

#endif