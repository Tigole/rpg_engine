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
	BasicFSM(const BasicFSM& b_fsm);
	BasicFSM& operator=(const BasicFSM& b_fsm);
	virtual ~BasicFSM();

	bool mt_Reset(void);

protected:
	IState* m_current_state;
	std::vector<std::pair<IState*, bool>> m_arr_states;
};


}

#endif // _BASIC_FSM_HPP
