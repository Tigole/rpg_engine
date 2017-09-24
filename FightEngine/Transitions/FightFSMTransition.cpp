#include "FightFSMTransition.hpp"
#include "Party/IParty.hpp"


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

		bool PartyTransition::mt_Reset(void)
		{
			return true;
		}

		fsm::IState* PartyDead::mt_Check(fsm::IState* current_state)
		{
			fsm::IState* l_ret(current_state);

			for (auto& party : m_target_parties)
			{
				for (auto& party_member : party->mt_Get_Members())
				{
					if (party_member->mt_Is_Dead())
					{
						l_ret = m_target_state;
					}
				}
			}

			return l_ret;
		}

		fsm::IState* PartyAlive::mt_Check(fsm::IState* current_state)
		{
			fsm::IState* l_ret(m_target_state);

			UNUSED_PARAMETER(current_state);

			for (auto& party : m_target_parties)
			{
				for (auto& party_member : party->mt_Get_Members())
				{
					if (!party_member->mt_Is_Dead())
					{
						l_ret = m_target_state;
					}
				}
			}
			return l_ret;
		}
	}
}
