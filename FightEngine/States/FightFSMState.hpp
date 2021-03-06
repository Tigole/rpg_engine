#ifndef _FIGHT_FSM_STATE_HPP
#define _FIGHT_FSM_STATE_HPP 1

#include "FSM/FSM.hpp"
#include "Character/ICharacter.hpp"
#include "FightEngine/Transitions/FightFSMTransition.hpp"
#include "FSM/FSMState.hpp"
#include <vector>

namespace fight
{
	namespace states
	{
		class FightState : public fsm::State
		{
		public:
			FightState(std::vector<ICharacter*>& characters);
			virtual ~FightState();
			bool mt_Reset(void);

			std::vector<ICharacter*>& m_characters;
		};

		class SelectSkill : public FightState
		{
		public:
			SelectSkill(std::vector<ICharacter*>& characters);
		protected:
			bool mt_Process(void);
		private:
			fsm::TrueTransition m_trans_true;
		};
		class UseSkill : public FightState
		{
		public:
			UseSkill(std::vector<ICharacter*>& characters);
		protected:
			bool mt_Process(void);
		private:
			transition::PartyDead m_trans_hero_dead;
			transition::PartyDead m_trans_ennemy_dead;
		};
	}
}


#endif // !_FIGHT_FSM_STATE_HPP
