#include "FightFSM.hpp"
#include "States/FightFSMState.hpp"

#include "Party/IParty.hpp"

namespace fight
{
	FightFSM::FightFSM()
		:m_fighters()
	{
		/** Nothing **/
	}

	void FightFSM::mt_Initialize(IParty& hero, std::vector<IParty*>& ennemies)
	{
		states::SelectSkill* state_sel_skill(new states::SelectSkill(m_fighters));
		states::UseSkill* state_use_skill(new states::UseSkill(m_fighters));
		fsm::EmptyState* state_game_over(new fsm::EmptyState());
		fsm::EmptyState* state_won(new fsm::EmptyState());

		fsm::TrueTransition* trans_true(new fsm::TrueTransition());
		transition::PartyDead* trans_hero_dead(new transition::PartyDead());
		transition::PartyDead* trans_ennemy_dead(new transition::PartyDead());
		transition::PartyAlive* trans_everybody_alive(new transition::PartyAlive());

		mt_Reset();

		/** Adding parties' characters to internal buffer for scheduling turns **/
		{
			for (auto& party_member : hero.mt_Get_Members())
				m_fighters.push_back(party_member);

			for (auto& ennemy_party : ennemies)
				for (auto& party_member : ennemy_party->mt_Get_Members())
					m_fighters.push_back(party_member);
		}

		/** Setting ennemies to each others **/
		{
			std::vector<IParty*> parties(ennemies);
			parties.push_back(&hero);

			for (auto& current_party : parties)
			{
				std::vector<IParty*> party_ennemies;
				for (auto& party : parties)
				{
					if (party != current_party)
						party_ennemies.push_back(party);
				}

				current_party->mt_Set_Ennemies(party_ennemies);
			}
		}

		/** Setting up state "Select skill" **/
		{
			trans_true->m_target_state = state_use_skill;

			state_sel_skill->m_arr_transitions.push_back(std::make_pair(trans_true, true));
		}

		/** Setting up state "Use skill" **/
		{
			trans_hero_dead->m_target_parties.push_back(&hero);
			trans_hero_dead->m_target_state = state_game_over;
			for (auto& ennemy_party : ennemies)
				trans_ennemy_dead->m_target_parties.push_back(ennemy_party);
			trans_ennemy_dead->m_target_state = state_won;
			trans_everybody_alive->m_target_parties.push_back(&hero);
			for (auto& ennemy_party : ennemies)
				trans_everybody_alive->m_target_parties.push_back(ennemy_party);
			trans_everybody_alive->m_target_state = state_sel_skill;

			state_use_skill->m_arr_transitions.push_back(std::make_pair(trans_hero_dead, true));
			state_use_skill->m_arr_transitions.push_back(std::make_pair(trans_ennemy_dead, true));
			state_use_skill->m_arr_transitions.push_back(std::make_pair(trans_everybody_alive, true));
		}

		/** Setting up state "Game over" **/
		{
			/** Nothing **/
		}

		/** Setting up state "Won" **/
		{
			/** Nothing **/
		}

		/** Setting states to FSM **/
		{
			m_arr_states.push_back(std::make_pair(state_sel_skill, true));
			m_arr_states.push_back(std::make_pair(state_use_skill, true));
			m_arr_states.push_back(std::make_pair(state_game_over, true));
			m_arr_states.push_back(std::make_pair(state_won, true));

			mt_Add_Stop_State(state_won);
			mt_Add_Stop_State(state_game_over);

			m_current_state = state_sel_skill;
		}
	}

	bool FightFSM::mt_Reset(void)
	{
		m_fighters.resize(0);
		return fsm::BasicFSM::mt_Reset();
	}
}
