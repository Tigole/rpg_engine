#include "BasicFSM.hpp"
#include "FSM/State/IState.hpp"

namespace fsm
{

BasicFSM::BasicFSM()
 :	StatusHandlerFSM(),
	m_current_state(nullptr)
{
	/** Nothing **/
}

BasicFSM::~BasicFSM()
{
	reset();
}

bool BasicFSM::reset(void)
{
	for (auto& a : m_arr_states)
		if (a.second)
			delete a.first;

	return true;
}

}
