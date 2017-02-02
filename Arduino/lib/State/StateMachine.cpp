#include "StateMachine.h"


void StateMachine::setCurrentState(State<entity_type>* s)
{
  _CurrentState = s;
}

void StateMachine::setPreviousState(State<entity_type>* s)
{
  _PreviousState = s;
};

StateMachine::StateMachine(entity_type* owner)
{
  _Owner = s;
};

void StateMachine::update()
{
  if(_CurrentState) _CurrentState->execute(_Owner);
};

void StateMachine::changeState(State<entity_type>* s)
{
  _PreviousState = _CurrentState;
  _CurrentState->exit(_Owner);
  _CurrentState = s;
  _CurrentState->enter(_Owner);
};

void StateMachine::revertState()
{
  changeState(_PreviousState);
};

bool StateMachine::isInState(const State<entity_type>& s)
{
  //TODO: Not Implemented yet
  return false;
};
