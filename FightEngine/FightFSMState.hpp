#ifndef _FIGHT_FSM_STATE_HPP
#define _FIGHT_FSM_STATE_HPP 1

#include "FSM\FSM.hpp"
#include "Character\ICharacter.hpp"
#include "FightFSMTransition.hpp"
#include "FSM\FSMState.hpp"
#include <vector>

namespace fight
{
	namespace states
	{
		class FightState : public fsm::State
		{
		public:
			FightState();
			virtual ~FightState();
			bool reset(void);

			std::vector<ICharacter*>* m_characters;
		};

		class SelectSkill : public FightState
		{
		public:
			SelectSkill();
		protected:
			bool process(void);
		private:
			fsm::TrueTransition m_trans_true;
		};
		class UseSkill : public FightState
		{
		public:
			UseSkill();
		protected:
			bool process(void);
		private:
			transition::PartyDead m_trans_hero_dead;
			transition::PartyDead m_trans_ennemy_dead;
		};
	}
}


#endif // !_FIGHT_FSM_STATE_HPP