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
	IState* callProcess(void) { return this; }
	bool reset(void) { return true; }
};

}

#endif // _FSMSTATE_H
