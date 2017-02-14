#ifndef _EventHandler_h
#define _EventHandler_h

template <class TEventArgs> 
class EventHandler
{
public:
    virtual void handle(TEventArgs*) = 0;
};

#endif