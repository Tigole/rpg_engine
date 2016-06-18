#include "FightFSMState.hpp"


namespace fight
{
	namespace states
	{
		FightState::FightState()
			:m_characters(nullptr)
		{}

		FightState::~FightState()
		{}

		bool FightState::reset(void) 
		{
			return true;
		}

		SelectSkill::SelectSkill() 
		{
			/** Nothing **/
		}

		bool SelectSkill::process(void) 
		{
			bool l_b_ret(false);

			if (m_characters != nullptr)
			{
				l_b_ret = true;
				for (auto& it : *m_characters)
				{
					it->selectSkill();
				}
			}

			return true;
		}

		UseSkill::UseSkill() 
		{
			/** Nothing **/
		}

		bool UseSkill::process(void) 
		{
			bool l_b_ret(false);
			if (m_characters != nullptr)
			{
				l_b_ret = true;
				for (auto& a : *m_characters)
				{
					a->useSkill();
				}
			}
			return l_b_ret;
		}
	}
}