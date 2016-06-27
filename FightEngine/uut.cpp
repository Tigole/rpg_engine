#include "uut.hpp"

#include "Character/DBG_Character.hpp"
#include "FightEngine/Party.hpp"
#include "FightFSM.hpp"
#include "Logger/ILogger.h"
#include "FightEngine/SkillManager.hpp"
#include "FightEngine/ISkill.hpp"

#include "FightEngine/DamageSkill.hpp"

#include <iostream>

ISkill* createDamageSkill(const TiXmlElement& element)
{
	ISkill* l_ret(nullptr);
	std::string l_skill_name, l_tmp;
	int l_skill_damages;
	int l_fn_returned(TIXML_SUCCESS);
	DamageSkill::DamageSkillOperator l_skill_operator;
	
	/** name **/
	if (l_fn_returned == TIXML_SUCCESS)	l_fn_returned = element.QueryStringAttribute("name", &l_skill_name);

	/** damages **/
	if (l_fn_returned == TIXML_SUCCESS) l_fn_returned = element.QueryIntAttribute("damages", &l_skill_damages);

	/** operator **/
	if (l_fn_returned == TIXML_SUCCESS) l_fn_returned = element.QueryStringAttribute("operator", &l_tmp);
	if (l_fn_returned == TIXML_SUCCESS) l_skill_operator = DamageSkill::stringToOperator(l_tmp);

	/** new object **/
	if (l_fn_returned == TIXML_SUCCESS) l_ret = new DamageSkill(l_skill_name, l_skill_damages, l_skill_operator);
	
	return l_ret;
}

namespace uut
{

	void uut_Fight_std(void)
	{
		std::vector<ICharacter*> ennemies;
		DBG_Character hero("Hero", 50), ennemy("Ennemy", 10);
		Fight_States fsm_state(FS_Choose_Skill);
		ICharacter* source_character(nullptr), *target_character(nullptr);

		ennemies.resize(1, &ennemy);
		hero.setEnnemies(ennemies);
		ennemies[0] = &hero;
		ennemy.setEnnemies(ennemies);

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
				source_character->useSkill();
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
				log() << "FS_Game_Over\n";
				fsm_state = FS_Done;
				break;
			case FS_Fight_Won:
				log() << "FS_Fight_Won\n";
				fsm_state = FS_Done;
				break;
			case FS_Done:
				log() << "FS_Done\n";
				break;
			default:
				break;
			}
		} while (fsm_state != FS_Done);

	}

	void uut_Fight_obj(void)
	{
		fight::FightFSM fsm;
		int status;
		DBG_Character hero("Hero", 100), ennemy("Ennemy", 50);
		std::vector<ICharacter*> fighters;
		Party hero_party, ennemy_party;
		std::vector<IParty*> ennemies_party;

		log().entranceFunction(FUNCTION_NAME);

		fighters.push_back(&hero);
		fighters.push_back(&ennemy);

		hero_party.addMember(&hero);
		ennemy_party.addMember(&ennemy);
		ennemies_party.push_back(&ennemy_party);

		fsm.initialize(hero_party, ennemies_party);

		do
		{
			status = fsm.process();
		} while (status == fsm::StatusHandlerFSM::STATUS_FSM_RUNNING);

		log() << "fsm ended with status : " << fsm.formatStatus(status) << "\n";
		log().exitFunction();
	}
	void uut_TestLoadingSkills(void)
	{
		SkillManager sm;
		std::vector<SkillManagerLoader> loaders;
		std::string file_path("C:/Users/Janniere Sylvain/Documents/Visual Studio 2015/Projects/projeay/Skills.xml");
		std::vector<std::string> skills_names;
		DBG_Character c("JaJa", 50);

		log().entranceFunction(FUNCTION_NAME);

		skills_names.push_back("skill test ADD");
		skills_names.push_back("skill test MINUS");
		skills_names.push_back("skill test MULTIPLY");
		skills_names.push_back("skill test DIVIDE");
		skills_names.push_back("skill test PERCENT");
		skills_names.push_back("skill test RAW");

		loaders.push_back(SkillManagerLoader("DamageSkill", createDamageSkill));

		log() << sm.load(file_path, loaders) << "\n";

		log().startBlock("testing getting skills");

		for (auto& skill_name : skills_names)
		{
			std::unique_ptr<ISkill> skill;
			log() << "getting " << skill_name << "\n";
			skill = std::move(sm.getSkill(skill_name, c));
			log() << skill.get() << "\n";
		}

		log().endBlock();

		log().exitFunction();
	}
}
