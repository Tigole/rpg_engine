#ifndef _ITRANSITION_HPP
#define _ITRANSITION_HPP 1

#include "Miscellaneous.hpp"
#include "FSM/State/IState.hpp"

namespace fsm
{

/**
	\class ITransition
	\brief Base class for a transition

	\fn IState* check(IState* p_current_state)
	\brief Method used to check if conditions are all good
	\return nullptr on error, p_current_state if conditions are not good, the next otherwise
**/

class ITransition : public misc::Resetable
{
public:
	virtual ~ITransition(){}

	virtual IState* mt_Check(IState* p_current_state) = 0;
};

}

#endif // _ITRANSITION_HPP
