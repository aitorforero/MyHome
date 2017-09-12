#ifndef BUTTONEVENTHANDLERSTATE_H
#define BUTTONEVENTHANDLERSTATE_H

#include <State.h>
#include "ButtonEventHandler.h"

template <class t> class ButtonEventHandlerState : public State<t>, public ButtonEventHandler<t>
{
    public:
      virtual void enter(t* rc){DEBUG_PRINT("Enter");};
      virtual void execute(t* rc){DEBUG_PRINT("Execute");};
      virtual void exit(t* rc){DEBUG_PRINT("Exit");};
      virtual void onLeftButtonClick(t* rc){DEBUG_PRINT("Left Click");};
      virtual void onRightButtonClick(t* rc){DEBUG_PRINT("Right Click");};
      virtual void onLeftButtonDown(t* rc){DEBUG_PRINT("Left Down");};
      virtual void onRightButtonDown(t* rc){DEBUG_PRINT("Right Down");};
      virtual void onLeftButtonUp(t* rc){DEBUG_PRINT("Left Up");};
      virtual void onRightButtonUp(t* rc){DEBUG_PRINT("Right Up");};
};

#endif