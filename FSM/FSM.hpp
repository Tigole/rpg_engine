#ifndef _FSM_H
#define _FSM_H 1

#include "FSM/BasicFSM.hpp"
#include "FSM/StatusHandlerFSM.hpp"
#include <vector>

/**
	\class CyclicFSM
	\brief Represent a cyclic FSM
**/

namespace fsm
{

class CyclicFSM : public BasicFSM
{
public:
	virtual ~CyclicFSM(){}

	virtual int mt_Process(void);
};

/**
	\class SequentialFSM
	\brief Represent a sequential FSM

	\fn void addStopState(IState* stop_state)
	\brief Allows to add a state that should be interpreted as a stop state
	\details If the current state is a state previously added as a stop state, process will return SEQUENTIAL_STOP_STATE_REACHED
**/

class SequentialFSM : public BasicFSM
{
public:

	enum SequentialFSM_Status
	{
		SEQUENTIAL_STOP_STATE_REACHED = STATUS_FSM_STATUS_MAX,

		SEQUENTIAL_FSM_STATUX_MAX
	};

	SequentialFSM();
	virtual ~SequentialFSM(){}

	virtual int mt_Process(void);

protected:

	void mt_Add_Stop_State(IState* stop_state, int return_value = SEQUENTIAL_STOP_STATE_REACHED);

private:

	std::vector<std::pair<IState*, int>> m_stop_states;
};

}


#endif // _FSM_H
