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

		bool FightState::reset(void)
		{
			return fsm::State::reset();
		}

		SelectSkill::SelectSkill(std::vector<ICharacter*>& characters)
			:FightState(characters),
			m_trans_true()
		{
			/** Nothing **/
		}

		bool SelectSkill::process(void)
		{
			bool l_ret(true);

			for (auto& it : m_characters)
			{
				it->selectSkill();
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

		bool UseSkill::process(void)
		{
			bool l_b_ret(true);

			for (auto& a : m_characters)
			{
				a->useSkill();
			}

			return l_b_ret;
		}
	}
}
