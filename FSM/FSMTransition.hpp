#ifndef _FSM_TRANSITION_HPP
#define _FSM_TRANSITION_HPP 1

#include "FSM\Transition\Transition.hpp"

namespace fsm
{

/**
	\class ITransition
	\brief Base class for a transition

	\fn IState* check(IState* p_current_state)
	\brief Method used to check if conditions are all good
	\return nullptr on error, p_current_state if conditions are not good, the next otherwise
**/

class TrueTransition : public Transition
{
public:
	TrueTransition(){}

	IState* check(IState* current_state) {UNUSED_PARAMETER(current_state); return m_target_state;}
	bool reset(void) { return true; }
};

}

#endif // _FSM_TRANSITION_HPP
