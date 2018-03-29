#ifndef MQTTEVENTS_H
#define MQTTEVENTS_H

#include "ArduinoSTL.h"
#include <DebugUtils.h>
#include <Event.h>
#include <EventArgs.h>

class RoomControl;

class MQTTEventArgs : public EventArgs
{
        MQTTEventArgs(void* sender):EventArgs(sender) {};
};

class MQTTEventsHandler
{
    public:
      virtual void handleMQTTMessage(MQTTEventArgs* e){};
};

class MQTTEventsController
{
    private:
        RoomControl* _owner;
        Event<MQTTEventArgs> _message;  
    
    public:
        MQTTEventsController(RoomControl* owner):_owner(owner){};

        Event<MQTTEventArgs>* messageEvent(){return &_message;};  
       
    protected:
        void onMessage(MQTTName _MQTT) {
            cout << "on MQTTName: " << _MQTT  << "\n";
            MQTTEventArgs e(this, _MQTT);
            _down.raise(&e);
        };
        
        
};



#endif