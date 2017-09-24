#include "States.hpp"

namespace fsm
{

State::State()
 : m_arr_transitions()
{
	/** Nothing **/
}

State::~State()
{
	mt_Reset();
}

IState* State::mt_Call_Process(void)
{
	bool l_b(true);
	IState* l_p_ret(nullptr);

	l_b = mt_Process();

	if (l_b)
	{
		l_p_ret = this;
		for (unsigned int i = 0; (i < m_arr_transitions.size()) && (l_p_ret == this); i++)
			l_p_ret = m_arr_transitions[i].first->mt_Check(this);
	}

	return l_p_ret;
}


bool State::mt_Reset(void)
{
	for (auto& t : m_arr_transitions)
		if (t.second)
			delete t.first;
	return true;
}

EntryExitState::EntryExitState()
	:m_b_on_entry_must_be_done(true)
{
	/** Nothing **/
}

EntryExitState::~EntryExitState()
{
	/** Nothing **/
}

IState* EntryExitState::mt_Call_Process(void)
{
	bool l_b(true);
	IState* l_p_ret(this);

	if (m_b_on_entry_must_be_done)
	{
		l_b = mt_On_Entry();
	}

	if (l_b)
	{
		l_b = mt_Process();
	}

	if (l_b)
	{
		for (unsigned int i = 0; (i < m_arr_transitions.size()) && (l_p_ret == this); i++)
			l_p_ret = m_arr_transitions[i].first->mt_Check(this);
	}

	/** Next state won't be this one so : onExit **/
	if ((l_p_ret != nullptr) && (l_p_ret != this))
	{
		l_b = mt_On_Exit();
	}

	return l_p_ret;
}

bool EntryExitState::mt_Reset(void)
{
	m_b_on_entry_must_be_done = true;
	return true;
}

bool EntryExitState::mt_On_Entry(void)
{
	m_b_on_entry_must_be_done = false;
	return true;
}

bool EntryExitState::mt_On_Exit(void)
{
	m_b_on_entry_must_be_done = true;
	return true;
}

}
