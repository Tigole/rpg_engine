#ifndef _FIGHT_FSM_H
#define _FIGHT_FSM_H 1

#include "FSM/FSM.hpp"
#include "FSM\FSMState.hpp"
#include "FSM\FSMTransition.hpp"
#include "Character\ICharacter.hpp"

namespace fight
{

	class FightFSM : public fsm::SequentialFSM
	{
	public:
		FightFSM(const std::vector<ICharacter*>& fighters);
		void initialize(void);
		bool reset(void);

	private:
		std::vector<ICharacter*> m_fighters;
	};
}


#endif // !_FIGHT_FSM_H