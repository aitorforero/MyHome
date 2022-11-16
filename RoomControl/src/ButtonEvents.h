#ifndef BUTTONEVENTS_H
#define BUTTONEVENTS_H

#include "ArduinoSTL.h"
#include <DebugUtils.h>
#include <Event.h>
#include <EventArgs.h>

class RoomControl;

enum ButtonName {leftButton, rightButton, bothButtons};

class ButtonEventArgs : public EventArgs
{
    
    private:
        ButtonName _buttonName;
    
    public:
        ButtonName getButtonName(){
            cout << "getting " << _buttonName << "\n";
            return _buttonName;
        };
        void setButtonName(ButtonName buttonName){_buttonName = buttonName;};
        ButtonEventArgs(void* sender, ButtonName buttonName):EventArgs(sender), _buttonName(buttonName) {};
};

class ButtonEventsHandler
{
    public:
      virtual void handleButtonClick(ButtonEventArgs* e){};
      virtual void handleButtonDown(ButtonEventArgs* e){};
      virtual void handleButtonUp(ButtonEventArgs* e){};
};

class ButtonEventsController
{
    private:
        RoomControl* _owner;
        Event<ButtonEventArgs> _down;  
        Event<ButtonEventArgs> _up;  
        Event<ButtonEventArgs> _click;  
    
    public:
        ButtonEventsController(RoomControl* owner):_owner(owner){};

        Event<ButtonEventArgs>* downEvent(){return &_down;};  
        Event<ButtonEventArgs>* upEvent(){return &_up;};  
        Event<ButtonEventArgs>* clickEvent(){return &_click;};  
       
    protected:
        void onDown(ButtonName _button) {
            cout << "on ButtonName: " << _button  << "\n";
            ButtonEventArgs e(this, _button);
            _down.raise(&e);
        };
        
        void onUp(ButtonName _button) {
            cout << "on ButtonName: " << _button  << "\n";
            ButtonEventArgs e(this, _button);
           _up.raise(&e);
        };
        
        void onClick(ButtonName _button) {
            cout << "on ButtonName: " << _button  << "\n";
           ButtonEventArgs e(this, _button);
           _click.raise(&e);
        };
        
};



#endif