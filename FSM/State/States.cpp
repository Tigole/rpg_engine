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
	for (auto& t : m_arr_transitions)
	{
		if (t.second)
		{
			delete t.first;
		}
	}
	/** Nothing **/
}

IState* State::callProcess(void)
{
	bool l_b(true);
	IState* l_p_ret(nullptr);
	
	l_b = process();

	if (l_b)
	{
		l_p_ret = this;
		for (unsigned int i = 0; (i < m_arr_transitions.size()) && (l_p_ret == this); i++)
			l_p_ret = m_arr_transitions[i].first->check(this);
	}

	return l_p_ret;
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

IState* EntryExitState::callProcess(void)
{
	bool l_b(true);
	IState* l_p_ret(this);

	if (m_b_on_entry_must_be_done)
	{
		l_b = onEntry();
	}

	if (l_b)
	{
		l_b = process();
	}

	if (l_b)
	{
		for (unsigned int i = 0; (i < m_arr_transitions.size()) && (l_p_ret == this); i++)
			l_p_ret = m_arr_transitions[i].first->check(this);
	}

	/** Next state won't be this one so : onExit **/
	if ((l_p_ret != nullptr) && (l_p_ret != this))
	{
		l_b = onExit();
	}

	return l_p_ret;
}

bool EntryExitState::reset(void)
{
	m_b_on_entry_must_be_done = true;
	return true;
}

bool EntryExitState::onEntry(void)
{
	m_b_on_entry_must_be_done = false;
	return true;
}

bool EntryExitState::onExit(void)
{
	m_b_on_entry_must_be_done = true;
	return true;
}

}
