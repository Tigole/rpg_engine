#ifndef _FIGHT_FSM_TRANSITION_H
#define _FIGHT_FSM_TRANSITION_H 1

#include "FSM\FSMTransition.hpp"
#include "Character\ICharacter.hpp"

#include <vector>

namespace fight
{
	namespace transition
	{
		class CharacterTransition : public fsm::Transition
		{
		public:
			CharacterTransition();
			virtual ~CharacterTransition();
			bool reset(void);

			std::vector<ICharacter*> m_target_characters;

		};
		class CharactersDead : public CharacterTransition
		{
		public:
			fsm::IState* check(fsm::IState* current_state);
		};

		class CharactersAlive : public CharacterTransition
		{
		public:
			fsm::IState* check(fsm::IState* current_state);
		};
	}
}

#endif // !_FIGHT_FSM_TRANSITION_H
