#include <iostream>
#include <vector>

#include "Character/ICharacter.hpp"
#include "Character/DBG_Character.hpp"

#include "FightEngine\FightFSM.hpp"

using namespace std;


enum Fight_States
{
	FS_Choose_Skill,
	FS_Use_Skill,
	FS_Game_Over,
	FS_Fight_Won,
	FS_Done
};
void uut_Fight(ICharacter& hero, ICharacter& ennemy);
void uut_Fight(const std::vector<ICharacter*>& fighters);

int main(int argc, char** argv)
{
	DBG_Character hero("JaJa", 10), ennemy("Tigole", 5);
	std::vector<ICharacter*> fighters;

	fighters.push_back(&hero);
	fighters.push_back(&ennemy);

	uut_Fight(hero, ennemy);
	uut_Fight(fighters);

	system("PAUSE");
	return 0;
}

void uut_Fight(ICharacter& hero, ICharacter& ennemy)
{
	Fight_States fsm_state(FS_Choose_Skill);
	ICharacter* source_character(nullptr), *target_character(nullptr);

	do
	{
		switch (fsm_state)
		{
		case FS_Choose_Skill:
			/** Act **/
			hero.selectSkill();
			ennemy.selectSkill();
			source_character = &hero;
			target_character = &ennemy;
			/** Transition **/
			fsm_state = FS_Use_Skill;
			break;
		case FS_Use_Skill:
			/** Act **/
			source_character->useSkill(*target_character);
			if (!target_character->isDead())
			{
				std::swap(source_character, target_character);
			}

			/** Transition **/
			if (source_character == &hero)	/** All characters have played **/
			{
				if (hero.isDead())
				{
					fsm_state = FS_Game_Over;
				}
				else if (ennemy.isDead())
				{
					fsm_state = FS_Fight_Won;
				}
				else
				{
					fsm_state = FS_Choose_Skill;
				}
			}

			break;
		case FS_Game_Over:
			std::cout << "FS_Game_Over\n";
			fsm_state = FS_Done;
			break;
		case FS_Fight_Won:
			std::cout << "FS_Fight_Won\n";
			fsm_state = FS_Done;
			break;
		case FS_Done:
			std::cout << "FS_Done\n";
			break;
		default:
			break;
		}
	} while (fsm_state != FS_Done);

}

void uut_Fight(const std::vector<ICharacter*>& fighters)
{
	fight::FightFSM fsm(fighters);
	int status;

	do
	{
		status = fsm.process();
	} while (status == fsm::StatusHandlerFSM::STATUS_FSM_RUNNING);

	std::cout << fsm.formatStatus(status) << "\n";
}
