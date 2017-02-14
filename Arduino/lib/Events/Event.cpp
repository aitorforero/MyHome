

#include <List.h>
#include "EventHandler.h"

#include "Event.h"


template <class TEventArgs> 
void Event<TEventArgs>::addHandler(EventHandler<TEventArgs>* newHandler) {
	handlers.add(newHandler);
};

template <class TEventArgs> 
void Event<TEventArgs>::removeHandler(EventHandler<TEventArgs>* handler) {
	handlers.remove(handler);
};

template <class TEventArgs> 
void Event<TEventArgs>::raise(TEventArgs* args) {
	for(int i=0;i<handlers.Count();i++)
		handlers.items(i)->handle(args);
};