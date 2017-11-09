#ifndef _StateMachine_h
#define _StateMachine_h

#include <Stack.h>
#include "State.h"

template <class entity_type>
class StateMachine
{
	protected:
		entity_type* _Owner;
		Stack<State<entity_type>*> _StateStack;
		List<State<entity_type>*> _statesToDelete;
		
		State<entity_type>* getCurrent() {
		    if(_StateStack.isEmpty()){
		        return NULL;
		    } else {
		        return _StateStack.peek();
		    };  
		}


	public:
		StateMachine(entity_type* owner)
		{
			_Owner = owner;
		};

		virtual void revert() {
			if( !_StateStack.isEmpty()){
				getCurrent()->exit();
				_statesToDelete.add(_StateStack.pop());
			}
			getCurrent()->resume();
		}
		
		virtual void moveTo(State<entity_type>* s){
			if( !_StateStack.isEmpty()){
				getCurrent()->suspend();
			}
			
			_StateStack.push(s);
			getCurrent()->enter();
		}

		virtual void changeTo(State<entity_type>* s)	{
			if( !_StateStack.isEmpty()){
				getCurrent()->exit();
				_statesToDelete.add(_StateStack.pop());
			}
			
			_StateStack.push(s);
			getCurrent()->enter();
		};


		virtual void update()
		{
			while(_statesToDelete.count()>0) {
				State<entity_type>* toDelete = _statesToDelete.item(0);
				_statesToDelete.remove(toDelete);
				delete toDelete;
				
			}
			
			if( !_StateStack.isEmpty()){
				_StateStack.peek()->execute();
			}
		};

};

#endif
