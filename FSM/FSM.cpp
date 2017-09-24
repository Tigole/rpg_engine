#include "FSM.hpp"

#include <algorithm>

namespace fsm
{

bool operator==(const std::pair<IState*, int>& a, const IState* b)
{
	return (a.first == b);
}

int CyclicFSM::mt_Process(void)
{
	int l_ret = STATUS_FSM_ERROR;

	if (m_current_state != nullptr)
	{
		m_current_state = m_current_state->mt_Call_Process();
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

int SequentialFSM::mt_Process(void)
{
	int l_ret = STATUS_FSM_ERROR;
	std::vector<std::pair<IState*, int>>::const_iterator l_stop_state(std::find(m_stop_states.begin(), m_stop_states.end(), m_current_state));

	if (m_current_state != nullptr)
	{
		m_current_state = m_current_state->mt_Call_Process();
		l_ret = STATUS_FSM_RUNNING;
	}

	if (l_stop_state != m_stop_states.end())
	{
		l_ret = l_stop_state->second;
	}

	return l_ret;
}

void SequentialFSM::mt_Add_Stop_State(IState* stop_state, int return_value)
{
	m_stop_states.push_back(std::make_pair(stop_state, return_value));
}

}
