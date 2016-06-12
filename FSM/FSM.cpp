#include "FSM.hpp"

#include <algorithm>

namespace fsm
{

int CyclicFSM::process(void)
{
	int l_ret = STATUS_FSM_ERROR;

	if (m_current_state != nullptr)
	{
		m_current_state = m_current_state->callProcess();
		l_ret = STATUS_FSM_RUNNING;
	}

	return l_ret;
}


SequentialFSM::SequentialFSM()
	:BasicFSM(),
	m_stop_states()
{
	m_translation_table[SEQUENTIAL_STOP_STATE_REACHED] = "SEQUENTIAL_STOP_STATE_REACHED";
}

int SequentialFSM::process(void)
{
	int l_ret = STATUS_FSM_ERROR;

	if (m_current_state != nullptr)
	{
		m_current_state = m_current_state->callProcess();
		l_ret = STATUS_FSM_RUNNING;
	}

	if (std::find(m_stop_states.begin(), m_stop_states.end(), m_current_state) != m_stop_states.end())
	{
		l_ret = SEQUENTIAL_STOP_STATE_REACHED;
	}

	return l_ret;
}

void SequentialFSM::addStopState(IState* stop_state)
{
	m_stop_states.push_back(stop_state);
}

}
