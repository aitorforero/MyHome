

#include <List.h>
#include "EventHandler.h"

#include "Event.h"


template <class TEventArgs> 
void Event::addHandler(EventHandler<TEventArgs>* newHandler) {
	handlers.add(newHandler);
};

template <class TEventArgs> 
void Event::removeHandler(EventHandler<TEventArgs>* handler) {
	handlers.remove(handler);
};

template <class TEventArgs> 
void Event::raise(TEventArgs* args) {
	for(int i=0;i<handlers.Count();i++)
		handlers.items(i)->handle(args);
};