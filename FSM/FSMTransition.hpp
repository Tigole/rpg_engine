#ifndef _FSM_TRANSITION_HPP
#define _FSM_TRANSITION_HPP 1

#include "FSM/Transition/Transition.hpp"

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

class TogglableTransition : public Transition
{
public:
	TogglableTransition() : m_transition_flag(false){}

	IState* check(IState* current_state) { if (m_transition_flag == true) current_state = m_target_state; m_transition_flag = false; return current_state; }
	bool reset(void) { m_transition_flag = false; return true; }
	void setFlag(void) { m_transition_flag = true; }
protected:
	bool m_transition_flag;
};

}

#endif // _FSM_TRANSITION_HPP
