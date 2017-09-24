#ifndef _IFSM_H
#define _IFSM_H 1

#include "Miscellaneous.hpp"

/**
	\class IFSM
	\brief Provide basic methods to process and reset the state machine

	\fn int mt_Process(void)
	\brief Method used to process one step on the state machine
	\return an int representing the status of the state machine (implementation dependent)

	\fn const char* mt_Format_Status(int status) const
	\brief Methode used to parse status returned by method "process"
	\return the human understandable status of the state machine
**/

namespace fsm
{

class IFSM : public misc::Resetable
{
public:
	virtual ~IFSM(){}

	virtual int mt_Process(void) = 0;
	virtual const char* mt_Format_Status(int status) const = 0;
};

}


#endif // _IFSM_H
