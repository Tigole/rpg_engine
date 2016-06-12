#ifndef _BASIC_FSM_HPP
#define _BASIC_FSM_HPP 1

#include "StatusHandlerFSM.hpp"
#include "FSM/State/IState.hpp"

#include <vector>

namespace fsm
{

class BasicFSM : public StatusHandlerFSM
{
public:
	BasicFSM();
	virtual ~BasicFSM();

protected:
	IState* m_current_state;
	std::vector<std::pair<IState*, bool>> m_arr_states;
};


}

#endif // _BASIC_FSM_HPP
