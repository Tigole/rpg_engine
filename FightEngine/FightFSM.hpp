#ifndef _FIGHT_FSM_HPP
#define _FIGHT_FSM_HPP 1

#include "FSM/FSM.hpp"
#include "FSM/FSMState.hpp"
#include "FSM/FSMTransition.hpp"

class IParty;
class ICharacter;

namespace fight
{

	class FightFSM : public fsm::SequentialFSM
	{
	public:
		FightFSM();
		void mt_Initialize(IParty& hero, std::vector<IParty*>& ennemies);

	protected:
		bool mt_Reset(void);
	private:
		std::vector<ICharacter*> m_fighters;
	};
}


#endif // !_FIGHT_FSM_HPP
