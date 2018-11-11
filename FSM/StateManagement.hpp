#ifndef _STATE_MANAGEMENT_HPP
#define _STATE_MANAGEMENT_HPP 1

#include <unordered_map>
#include <unordered_set>

class IState
{
public:
	IState(){}
	virtual ~IState(){}

	virtual void mt_OnEntry(void) = 0;
	virtual void mt_OnExit(void) = 0;

	virtual void mt_Update(float delta_time_ms) = 0;
	virtual void mt_Draw(void) = 0;
protected:
};

template<typename StateEnumType>
class StateDependent
{
public:
	StateDependent() : m_current_state() {}
	~StateDependent() {}

	virtual void mt_OnEntry(const StateEnumType& state) = 0;
	void mt_Set_State(const StateEnumType& state)
	{
		m_current_state = state;
	}

protected:
	StateEnumType m_current_state;

};


template<class UpdateDataType, typename StateEnumType>
class StateManager
{
public:
	StateManager()
		:m_current_state(m_states.end())
	{}
	virtual ~StateManager()
	{}

	void mt_SetState(const StateEnumType& state_id)
	{
		auto l_it(m_states.find(state_id));
		if (l_it != m_states.end())
		{
			if (m_current_state != m_states.end())
			{
				m_current_state->second->mt_OnExit();
			}
			m_current_state = l_it;
			mt_NotifyOnEntry(state_id);
			m_current_state->second->mt_OnEntry();
		}
	}

	void mt_Update(const UpdateDataType& update_data)
	{
		if (m_current_state != m_states.end())
		{
			m_current_state->second->mt_Update(update_data);
		}
	}

	void mt_AddState(const StateEnumType& state_id, IState* state)
	{
		bool l_b_reset_end(false);

		if (state != nullptr)
		{
			l_b_reset_end = (m_current_state == m_states.end());

			m_states.emplace(state_id, state);

			if (l_b_reset_end == true)
			{
				m_current_state = m_states.end();
			}
		}
	}

	void mt_AddDependant(StateDependent<StateEnumType>* dep)
	{
		m_dependents.push_back(dep);
	}
	void mt_RemoveDependant(StateDependent<StateEnumType>* dep)
	{
		if (m_dependents.find(dep) != m_dependents.end())
			m_dependents.erase(m_dependents.find(dep));
	}

protected:
	void mt_NotifyOnEntry(const StateEnumType& state_id)
	{
		for (auto& l_dep : m_dependents)
		{
			l_dep->mt_OnEntry(state_id);
		}
	}
	std::vector<StateDependent<StateEnumType>*> m_dependents;
	std::unordered_map<StateEnumType, IState*> m_states;
	typename std::unordered_map<StateEnumType, IState*>::iterator m_current_state;
};


#endif // !_STATE_MANAGEMENT_HPP