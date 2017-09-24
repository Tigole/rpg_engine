#ifndef _ISTATE_H
#define _ISTATE_H 1

#include "Miscellaneous.hpp"

namespace fsm
{

/**
	\class IState
	\brief Base class for describing a state in a state machine

	\fn IState* callProcess(void)
	\brief Method used by state machine to call the process actions by the state
	\return nullptr if error, the next state to call otherwise (itself included)

	\fn bool onEntry(void)
	\brief Method used to initialize the state when entering the state
	\return false on error, true otherwise

	\fn bool onExit(void)
	\brief Method used to un-initialize the state when leaving it
**/

class IState : public misc::Resetable
{
public:
	virtual ~IState(){}

	virtual IState* mt_Call_Process(void) = 0;
};

}

#endif // _ISTATE_H
