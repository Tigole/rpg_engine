#ifndef _TRANSITION_HPP
#define _TRANSITION_HPP 1

#include "ITransition.hpp"

namespace fsm
{

/**
	\class Transition
	\brief Class adding a reference to the destination state of the transition

	\var IState* m_target_state
	\brief Target state of the transition
	\details Freeing memory is not provided by the object
**/

class Transition : public ITransition
{
public:
	Transition():m_target_state(nullptr){}
	Transition(const Transition& t):m_target_state(nullptr){(void)(t);}
	Transition& operator=(const Transition& t){(void)(t); m_target_state = nullptr; return *this;}
	virtual ~Transition(){}
	IState* m_target_state;
};

}

#endif // _TRANSITION_HPP
