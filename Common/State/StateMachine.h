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

		void pushState(State<entity_type>* s) {
			_StateStack.push(s);
			s->enter(_Owner);
		}


	public:
		StateMachine(entity_type* owner)
		{
			_Owner = owner;
		};

		virtual void revertState() {
			if(!_StateStack.isEmpty()){
				State<entity_type>* currentState = _StateStack.pop();
				currentState->exit(_Owner);
			}
			if(!_StateStack.isEmpty()) {
				State<entity_type>* previousState = _StateStack.peek();
				previousState->enter(_Owner);
			}
		}
		
		virtual void switchState(State<entity_type>* s){
			if( !_StateStack.isEmpty()){
				State<entity_type>* currentState = _StateStack.pop();
				currentState->exit(_Owner);
			}
			pushState(s);		
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
