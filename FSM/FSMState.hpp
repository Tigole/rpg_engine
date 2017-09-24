#ifndef _FSMSTATE_H
#define _FSMSTATE_H 1

#include "FSM/State/States.hpp"

namespace fsm
{

/**
	\class EmptyState
	\brief represent a state that doesn't do anything. Could be used as final state
**/

class EmptyState : public IState
{
public:
	IState* mt_Call_Process(void) { return this; }
	bool mt_Reset(void) { return true; }
};

class IdleState : public State
{
public:
	virtual ~IdleState(){}
protected:
	virtual bool mt_Process(void) { return true; }
};

}

#endif // _FSMSTATE_H
