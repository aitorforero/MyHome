#ifndef _StateMachine_h
#define _StateMachine_h

#include "State.h"

template <class entity_type>
class StateMachine
{
	private:
		entity_type* _Owner;
		State<entity_type> _CurrentState;
		State<entity_type> _PreviousState;
		void setCurrentState(State<entity_type>* s);
		void setPreviousState(State<entity_type>* s);
	public:
		StateMachine(entity_type* owner);

		void update();
		void changeState(State<entity_type>* s);
		void revertState();
		bool isInState(const State<entity_type>& s);
	
};

#endif
	