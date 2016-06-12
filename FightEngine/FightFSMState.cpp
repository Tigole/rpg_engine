#include "FightFSMState.hpp"


namespace fight
{
	namespace states
	{
		FightState::FightState()
			:m_characters()
		{}

		FightState::~FightState()
		{}

		bool FightState::reset(void) 
		{
			m_characters.resize(0);
			return true;
		}

		SelectSkill::SelectSkill() 
		{
			m_arr_transitions.push_back(std::make_pair(new fsm::TrueTransition(), true));
		}

		bool SelectSkill::process(void) 
		{
			//

			return true;
		}

		UseSkill::UseSkill() 
		{
			m_arr_transitions.push_back(std::make_pair(new transition::CharactersDead(), true));
			m_arr_transitions.push_back(std::make_pair(new transition::CharactersDead(), true));
			m_arr_transitions.push_back(std::make_pair(new transition::CharactersAlive(), true));
		}

		bool UseSkill::process(void) 
		{
			return true;
		}
	}
}