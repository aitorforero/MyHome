#ifndef MQTTEVENTS_H
#define MQTTEVENTS_H

#include "ArduinoSTL.h"
#include <string.h>
#include <DebugUtils.h>
#include <Event.h>
#include <EventArgs.h>

class RoomControl;

class MQTTMessageEventArgs : public EventArgs
{
    private:
        const char* _message;
        const char* _topic;

    
    public:
        void getTopic(char* topic)
        {
            strncpy(topic, _topic, strlen(_topic));
        };

        void getMessage(char* message)
        {
            strncpy(message, _message, strlen(_message));
            DEBUG_PRINT(message << "****")
            DEBUG_PRINT(_message << "****") 
        };



        MQTTMessageEventArgs(void* sender,const char* topic, const char* message):EventArgs(sender)
        {
            _topic = topic;
            _message = message;
            DEBUG_PRINT(_message)
        };

        ~MQTTMessageEventArgs()
        {
        }
};

class MQTTEventsHandler
{
    public:
      virtual void handleMQTTMessage(MQTTMessageEventArgs* e){};
};

class MQTTEventsController
{
    private:
        RoomControl* _owner;
        Event<MQTTMessageEventArgs> _message;  
    
    public:
        MQTTEventsController(RoomControl* owner):_owner(owner){};

        Event<MQTTMessageEventArgs>* messageEvent(){return &_message;};  
       
    protected:
        void onMessage(const char * topic, const char * message) {
            MQTTMessageEventArgs e(this, topic, message);
            _message.raise(&e);
        };
        
        
};



#endif