#ifndef _FIGHT_FSM_TRANSITION_HPP
#define _FIGHT_FSM_TRANSITION_HPP 1

#include "FSM\FSMTransition.hpp"
#include "Character\ICharacter.hpp"

#include <vector>

class IParty;

namespace fight
{
	namespace transition
	{
		class PartyTransition : public fsm::Transition
		{
		public:
			PartyTransition();
			virtual ~PartyTransition();
			bool reset(void);

			std::vector<IParty*> m_target_parties;

		};
		class PartyDead : public PartyTransition
		{
		public:
			fsm::IState* check(fsm::IState* current_state);
		};

		class PartyAlive : public PartyTransition
		{
		public:
			fsm::IState* check(fsm::IState* current_state);
		};
	}
}

#endif // !_FIGHT_FSM_TRANSITION_HPP
