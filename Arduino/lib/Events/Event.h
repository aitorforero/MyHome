#ifndef _Event_h
#define _Event_h

#include <List.h>
#include "EventHandler.h"

template <class TEventArgs> 
class Event
{
public:
    void addHandler(EventHandler<TEventArgs>*);
	void removeHandler(EventHandler<TEventArgs>*);
	void raise(TEventArgs* args);
	Event();
private:
	List<EventHandler<TEventArgs>> handlers;
};

#endif

