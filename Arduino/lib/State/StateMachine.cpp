#include "StateMachine.h"

template <class entity_type>   
void StateMachine<entity_type>::setCurrentState(State<entity_type>* s)
{
  _CurrentState = s;
}

template <class entity_type> 
void StateMachine<entity_type>::setPreviousState(State<entity_type>* s)
{
  _PreviousState = s;
};

template <class entity_type> 
StateMachine<entity_type>::StateMachine(entity_type* owner)
{
  _Owner = owner;
};

template <class entity_type> 
void StateMachine<entity_type>::update()
{
  if(_CurrentState) _CurrentState->execute(_Owner);
};


template <class entity_type> 
void StateMachine<entity_type>::changeState(State<entity_type>* s)
{
  _PreviousState = _CurrentState;
  _CurrentState->exit(_Owner);
  _CurrentState = s;
  _CurrentState->enter(_Owner);
};

template <class entity_type> 
void StateMachine<entity_type>::revertState()
{
  changeState(_PreviousState);
};

template <class entity_type> 
bool StateMachine<entity_type>::isInState(const State<entity_type>& s)
{
  //TODO: Not Implemented yet
  return false;
};
