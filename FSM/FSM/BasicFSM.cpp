#include "BasicFSM.hpp"
#include "FSM/State/IState.hpp"

namespace fsm
{

BasicFSM::BasicFSM()
 :	StatusHandlerFSM(),
	m_current_state(nullptr),
	m_arr_states()
{
	/** Nothing **/
}

BasicFSM::~BasicFSM()
{
	mt_Reset();
}

bool BasicFSM::mt_Reset(void)
{
	for (auto& a : m_arr_states)
		if (a.second)
			delete a.first;

	return true;
}

}
