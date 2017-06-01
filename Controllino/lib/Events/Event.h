#ifndef _Event_h
#define _Event_h

#include <FastDelegate.h>
#include <List.h>

using namespace fastdelegate;

template <class TEventArgs> 
class Event
{
	public:
		typedef FastDelegate1<TEventArgs*, void> Handler;
		typedef void(*callbackHandler)(TEventArgs*);

		void addHandler(Handler h)
		{
				handlers->add(h);
		};

		void removeHandler(Handler h)
		{
				handlers->remove(h);
		};
		
		void addHandler(callbackHandler h)
		{
				callbackHandlers->add(h);
		};

		void removeHandler(callbackHandler h)
		{
				callbackHandlers->remove(h);
		};

		void raise(TEventArgs* args) {
				for(int i=0;i<handlers->count();i++)
				{
					(handlers->item(i))(args);				
				}
				for(int i=0;i<callbackHandlers->count();i++)
				{
					(callbackHandlers->item(i))(args);				
				}
		};

		Event()
		{
				handlers = new List<Handler>;
				callbackHandlers = new List<callbackHandler>;
		};

	
		private:
			List<Handler>* handlers;
			List<callbackHandler>* callbackHandlers;
};

#endif

