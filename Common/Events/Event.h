#ifndef _Event_h
#define _Event_h

#include <Arduino.h>
#include <FastDelegate.h>
#include <List.h>

using namespace fastdelegate;

template <class TEventArgs> 
class Event
{
	public:
		typedef FastDelegate1<TEventArgs*, void> Handler;

		void addHandler(Handler h)
		{
				handlers->add(h);
		};

		void removeHandler(Handler h)
		{
				handlers->remove(h);
		};
		
		void raise(TEventArgs* args) { 
				for(int i=0;i<handlers->count();i++)
				{   
					(handlers->item(i))(args);				
				}
		};

		Event()
		{
				handlers = new List<Handler>;
		};

	
		private:
			List<Handler>* handlers;
};

#endif

