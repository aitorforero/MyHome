#ifndef _StateMachine_h
#define _StateMachine_h


#include <DebugUtils.h>
#include <stack>
#include <ArduinoSTL.h>
#include <vector>
#include "State.h"

using namespace std;


template <class entity_type>
class StateMachine
{
	protected:
		entity_type* _Owner;
		stack<State<entity_type>*> _StateStack;
		vector<State<entity_type>*> _statesToDelete;
		
		State<entity_type>* getCurrent() {
			State<entity_type>* res = nullptr;
 	        if(!_StateStack.empty())
			{
				res = _StateStack.top();
			} 
			else
			{
				ERROR_PRINT("No existe estado actual")
			};

			return res;
		}

		void exitCurrent()
		{
			State<entity_type>* s = _StateStack.top();
			_StateStack.pop();
			s->suspend();
			s->exit();
			_statesToDelete.push_back(s);
		}

		void enterState(State<entity_type>* s)
		{
			_StateStack.push(s);
			s->enter();			
			s->resume();			
		}


	public:
		StateMachine(entity_type* owner)
		{
			_Owner = owner;
		};

		virtual void revert() {
			exitCurrent();
			getCurrent()->resume();
		}
		
		virtual void moveTo(State<entity_type>* s){
			if( !_StateStack.empty()){
				getCurrent()->suspend();
			}
			
			enterState(s);
		}

		virtual void changeTo(State<entity_type>* s) 
		{
			if( !_StateStack.empty())
			{
				exitCurrent();
			}
			enterState(s);
		};


		virtual void update()
		{
			while(!_statesToDelete.empty()) {
				State<entity_type>* toDelete = _statesToDelete.back();
				_statesToDelete.pop_back();
				// delete toDelete;
			}
			
			if( !_StateStack.empty()){
				getCurrent()->execute();
			}
		};

};

#endif
