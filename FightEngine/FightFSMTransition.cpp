#include "FightFSMTransition.hpp"
#include "IParty.hpp"


namespace fight
{
	namespace transition
	{

		PartyTransition::PartyTransition()
			:m_target_parties()
		{
			/** Nothing **/
		}

		PartyTransition::~PartyTransition()
		{
			/** Nothing **/
		}

		bool PartyTransition::reset(void)
		{
			return true;
		}

		fsm::IState* PartyDead::check(fsm::IState* current_state)
		{
			fsm::IState* l_ret(current_state);

			for (auto& party : m_target_parties)
			{
				for (auto& party_member : party->getMembers())
				{
					if (party_member->isDead())
					{
						l_ret = m_target_state;
					}
				}
			}

			return l_ret;
		}

		fsm::IState* PartyAlive::check(fsm::IState* current_state)
		{
			fsm::IState* l_ret(m_target_state);

			UNUSED_PARAMETER(current_state);

			for (auto& party : m_target_parties)
			{
				for (auto& party_member : party->getMembers())
				{
					if (!party_member->isDead())
					{
						l_ret = m_target_state;
					}
				}
			}
			return l_ret;
		}
	}
}
