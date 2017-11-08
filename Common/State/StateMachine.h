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
			if(!_StateStack.isEmpty()){
				State<entity_type>* currentState = _StateStack.pop();
				currentState->exit(_Owner);
			}
			if(!_StateStack.isEmpty()) {
				State<entity_type>* previousState = _StateStack.peek();
				previousState->enter(_Owner);
			}
		}
		
		virtual void (State<entity_type>* s){
			if( !.isEmpty()){
				State<entity_type>* currentState = _StateStack.pop();
				currentState->(_Owner);
			}
			
				
		}

		virtual void changeState(State<entity_type>* s)	{
			if( !_StateStack.isEmpty()){
				State<entity_type>* currentState = _StateStack.peek();
				currentState->exit(_Owner);
			}
			pushState(s);
		};


		virtual void update()
		{
			if( !_StateStack.isEmpty()){
				_StateStack.peek()->execute(_Owner);
			}
		};

};

#endif
