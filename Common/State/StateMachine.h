#ifndef _StateMachine_h
#define _StateMachine_h



#include <DebugUtils.h>
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
			DEBUG_PRINT("Getting current...")
			State<entity_type>* res = nullptr;
 	        if(!_StateStack.isEmpty()){
				DEBUG_PRINT("Peeking from stack...")
				res = _StateStack.peek();
			};

			DEBUG_PRINT("Memory address: ")
			DEBUG_PRINT((int) res)

			return res;
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

		virtual void changeTo(State<entity_type>* s) 
		{
			DEBUG_PRINT("Entering changeTo...")
			if( !_StateStack.isEmpty())
			{
				DEBUG_PRINT("Exit from previous state...")
				getCurrent()->exit();
				DEBUG_PRINT("Adding to delete...")
				_statesToDelete.add(_StateStack.pop());
			}
			
			_StateStack.push(s);
			getCurrent()->enter();
			DEBUG_PRINT("Exit from changeTo!")
		};


		virtual void update()
		{
			while(_statesToDelete.count()>0) {
				DEBUG_PRINT("Deleting previous states...")
				State<entity_type>* toDelete = _statesToDelete.item(0);
				_statesToDelete.remove(toDelete);
				delete toDelete;
				DEBUG_PRINT("Deleted!")
			}
			
			if( !_StateStack.isEmpty()){
				DEBUG_PRINT("Executing current state")
				State<entity_type>* current = getCurrent();
				current->execute();
			}
		};

};

#endif
