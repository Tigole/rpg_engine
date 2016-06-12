#include "FightFSMTransition.hpp"


namespace fight
{
	namespace transition
	{

		CharacterTransition::CharacterTransition()
			:m_target_characters()
		{
			/** Nothing **/
		}
		
		CharacterTransition::~CharacterTransition()
		{
			/** Nothing **/
		}

		bool CharacterTransition::reset(void)
		{
			m_target_characters.resize(0);
			return true;
		}

		fsm::IState* CharactersDead::check(fsm::IState* current_state)
		{
			std::vector<ICharacter*>::iterator it;
			fsm::IState* l_ret(current_state);
			for (it = m_target_characters.begin(); (it != m_target_characters.end()) && (l_ret == current_state); it++)
			{
				if ((*it)->isDead())
				{
					l_ret = m_target_state;
				}
			}
			return l_ret;
		}

		fsm::IState* CharactersAlive::check(fsm::IState* current_state)
		{
			std::vector<ICharacter*>::iterator it;
			fsm::IState* l_ret(m_target_state);
			for (it = m_target_characters.begin(); (it != m_target_characters.end()) && (l_ret == m_target_state); it++)
			{
				if ((*it)->isDead())
				{
					l_ret = current_state;
				}
			}
			return l_ret;
		}
	}
}