#ifndef _IFSM_H
#define _IFSM_H 1

#include "Miscellaneous.hpp"

/**
	\class IFSM
	\brief Provide basic methods to process and reset the state machine

	\fn bool reset(void)
	\brief Method used to reset the state machine in its initial state
	\return true if reset succeeded, false otherwise

	\fn int process(void)
	\brief Method used to process one step on the state machine
	\return an int representing the status of the state machine (implementation dependent)

	\fn const char* formatStatus(int status) const
	\brief Methode used to parse status returned by method "process"
	\return the human understandable status of the state machine
**/

namespace fsm
{

class IFSM : public misc::Resetable
{
public:
	virtual ~IFSM(){}

	virtual void initialize(void) = 0;
	virtual int process(void) = 0;
	virtual const char* formatStatus(int status) const = 0;
};

}


#endif // _IFSM_H
