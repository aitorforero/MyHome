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
        char* _message;
        char* _topic;
        unsigned int _messageLength;
        unsigned int _topicLength;

    
    public:
        void getTopic(char* topic)
        {
            strncpy(topic, _topic, _topicLength);
        };

        void getMessage(char* message)
        {
            strncpy(message, _message, _messageLength);
        };

        unsigned int getMessageLength()
        {
            return _messageLength;
        } 

        unsigned int getTopicLength()
        {
            return _topicLength;
        } 

        MQTTMessageEventArgs(void* sender,const char* topic, const char* message):EventArgs(sender)
        {
            _topicLength = strlen(topic);
            _messageLength = strlen(message);


            _topic = new char[_topicLength+1]();
           _message = new char[_messageLength+1]();
            strncpy(_topic, topic, _topicLength);
            strncpy(_message, message, _messageLength);

        };

        ~MQTTMessageEventArgs()
        {
            delete _topic;
            delete _message;
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
            DEBUG_PRINT("Message arrived")
            MQTTMessageEventArgs e(this, topic, message);
            _message.raise(&e);
            DEBUG_PRINT("Raised")
        };
        
        
};



#endif