#ifndef _StateMachine_h
#define _StateMachine_h

#include <Arduino.h>
#include <Debug.h>
#include "State.h"

template <class entity_type>
class StateMachine
{
	private:

		entity_type* _Owner;
		State<entity_type>* _CurrentState;
		State<entity_type>* _PreviousState;
		void setCurrentState(State<entity_type>* s)
		{
			_CurrentState = s;
		};

		void setPreviousState(State<entity_type>* s)
		{
			_PreviousState = s;
		};

	public:
		StateMachine(entity_type* owner)
		{
			_Owner = owner;
			_CurrentState = NULL;
			_PreviousState = NULL;
		};

		void update()
		{
			  if(_CurrentState) _CurrentState->execute(_Owner);
		};

		void changeState(State<entity_type>* s)
		{
			_PreviousState = _CurrentState;
			if(_CurrentState)	_CurrentState->exit(_Owner);
			_CurrentState = s;
			_CurrentState->enter(_Owner);
		};


		void revertState()
		{
		  changeState(_PreviousState);
		};


};

#endif
