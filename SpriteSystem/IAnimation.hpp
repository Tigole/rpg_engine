#ifndef _IANIMATION_HPP
#define _IANIMATION_HPP 1

#include "FSM/FSM.hpp"

class IAnimation// : public fsm::SequentialFSM
{
public:
	virtual ~IAnimation(){}

	//virtual bool mt_Reset(void);

	virtual void mt_Update(float delta_time_ms) = 0;
	virtual void mt_Play(void) = 0;
	virtual void mt_Stop(void) = 0;

protected:
	//
};

#endif // !_IANIMATION_HPP
