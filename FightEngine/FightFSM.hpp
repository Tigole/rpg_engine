#ifndef _FIGHT_FSM_HPP
#define _FIGHT_FSM_HPP 1

#include "FSM\FSM.hpp"
#include "FSM\FSMState.hpp"
#include "FSM\FSMTransition.hpp"

class IParty;
class ICharacter;

namespace fight
{

	class FightFSM : public fsm::SequentialFSM
	{
	public:
		FightFSM(IParty& hero, std::vector<IParty*>& ennemies);
		void initialize(void);
		bool reset(void);

	private:
		std::vector<ICharacter*> m_fighters;
	};
}


#endif // !_FIGHT_FSM_HPP