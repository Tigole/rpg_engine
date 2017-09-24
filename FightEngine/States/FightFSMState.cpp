#include "FightFSMState.hpp"


namespace fight
{
	namespace states
	{
		FightState::FightState(std::vector<ICharacter*>& characters)
			:m_characters(characters)
		{}

		FightState::~FightState()
		{}

		bool FightState::mt_Reset(void)
		{
			return fsm::State::mt_Reset();
		}

		SelectSkill::SelectSkill(std::vector<ICharacter*>& characters)
			:FightState(characters),
			m_trans_true()
		{
			/** Nothing **/
		}

		bool SelectSkill::mt_Process(void)
		{
			bool l_ret(true);

			for (auto& it : m_characters)
			{
				it->mt_Select_Skill();
			}

			return l_ret;
		}

		UseSkill::UseSkill(std::vector<ICharacter*>& characters)
			:FightState(characters),
			m_trans_hero_dead(),
			m_trans_ennemy_dead()
		{
			/** Nothing **/
		}

		bool UseSkill::mt_Process(void)
		{
			bool l_b_ret(true);

			for (auto& a : m_characters)
			{
				a->mt_Use_Skill();
			}

			return l_b_ret;
		}
	}
}
