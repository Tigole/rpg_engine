#ifndef _IANIMATION_HPP
#define _IANIMATION_HPP 1

#include "FSM/FSM.hpp"

class IAnimation : public fsm::SequentialFSM
{
public:
	virtual ~IAnimation(){}

	virtual bool reset(void);

protected:
	//
};

#endif // !_IANIMATION_HPP
