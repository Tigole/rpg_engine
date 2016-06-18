#include "FightFSM.hpp"
#include "FightFSMState.hpp"

#include "IParty.hpp"

namespace fight
{
	FightFSM::FightFSM(IParty& hero, std::vector<IParty*>& ennemies)
		:m_fighters()
	{
		states::SelectSkill* sel_skill(new states::SelectSkill());
		states::UseSkill* use_skill(new states::UseSkill());
		fsm::EmptyState* game_over(new fsm::EmptyState());
		fsm::EmptyState* won(new fsm::EmptyState());

		fsm::TrueTransition* true_trans(new fsm::TrueTransition());
		transition::PartyDead* hero_dead(new transition::PartyDead());
		transition::PartyDead* ennemy_dead(new transition::PartyDead());
		transition::PartyAlive* everybody_alive(new transition::PartyAlive());

		for (auto& party_member : hero.getMembers())
			m_fighters.push_back(party_member);

		for (auto& ennemy_party : ennemies)
			for (auto& party_member : ennemy_party->getMembers())
				m_fighters.push_back(party_member);

		/** STA Select skill **/
		true_trans->m_target_state = use_skill;

		sel_skill->m_arr_transitions.push_back(std::make_pair(true_trans, true));
		sel_skill->m_characters = &m_fighters;
		/** END Select skill **/

		/** STA Use skill **/
		hero_dead->m_target_parties.push_back(&hero);
		hero_dead->m_target_state = game_over;
		for (auto& ennemy_party : ennemies)
			ennemy_dead->m_target_parties.push_back(ennemy_party);
		ennemy_dead->m_target_state = won;
		everybody_alive->m_target_parties.push_back(&hero);
		for (auto& ennemy_party : ennemies)
			everybody_alive->m_target_parties.push_back(ennemy_party);
		everybody_alive->m_target_state = sel_skill;

		use_skill->m_characters = &m_fighters;
		use_skill->m_arr_transitions.push_back(std::make_pair(hero_dead, true));
		use_skill->m_arr_transitions.push_back(std::make_pair(ennemy_dead, true));
		use_skill->m_arr_transitions.push_back(std::make_pair(everybody_alive, true));
		/** END Use skill **/

		/** STA Game over **/
			/** Nothing **/
		/** END Game over **/
		/** STA Won **/
			/** Nothing **/
		/** END Won **/

		m_arr_states.push_back(std::make_pair(sel_skill, true));
		m_arr_states.push_back(std::make_pair(use_skill, true));
		m_arr_states.push_back(std::make_pair(game_over, true));
		m_arr_states.push_back(std::make_pair(won, true));

		addStopState(won);
		addStopState(game_over);

		m_current_state = sel_skill;
	}

	void FightFSM::initialize(void)
	{
		/** Nothing **/
	}

	bool FightFSM::reset(void)
	{
		return true;
	}
}