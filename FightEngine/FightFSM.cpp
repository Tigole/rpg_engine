#include "FightFSM.hpp"
#include "FightFSMState.hpp"

namespace fight
{
	FightFSM::FightFSM(const std::vector<ICharacter*>& fighters)
		:m_fighters(fighters)
	{
		m_arr_states.push_back(std::make_pair(new states::SelectSkill(), true));
		m_arr_states.push_back(std::make_pair(new states::UseSkill(), true));
		m_arr_states.push_back(std::make_pair(new fsm::EmptyState(), true));
		m_arr_states.push_back(std::make_pair(new fsm::EmptyState(), true));

		m_current_state = m_arr_states.front().first;
	}

	void FightFSM::initialize(void)
	{
		/** Nothing **/
	}

	bool FightFSM::reset(void)
	{
		return true;
	}
}