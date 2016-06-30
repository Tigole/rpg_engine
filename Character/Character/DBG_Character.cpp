#include "DBG_Character.hpp"
#include "Logger/ILogger.h"

#include "Skill/Skill/DamageSkill.hpp"

#include "Skill/SkillManager.hpp"
#include "Skill/ISkill.hpp"

DBG_Character::DBG_Character(const char * name, int hp_max)
	:BasicCharacter(name, misc::Gauge<int>(hp_max)),
	m_skill_index(0)
{
	m_skills.resize(6);
	/*m_skills[0].reset(new DamageSkill("test attack ADD", 1, DamageSkill::DSO_ADD));
	m_skills[1].reset(new DamageSkill("test attack MINUS", 1, DamageSkill::DSO_MINUS));
	m_skills[2].reset(new DamageSkill("test attack MULTIPLY", 2, DamageSkill::DSO_MULTIPLY));
	m_skills[3].reset(new DamageSkill("test attack DIVIDE", 1, DamageSkill::DSO_DIVIDE));
	m_skills[4].reset(new DamageSkill("test attack PERCENT", 50, DamageSkill::DSO_PERCENT));
	m_skills[5].reset(new DamageSkill("test attack RAW", 1, DamageSkill::DSO_RAW));*/
}

DBG_Character::~DBG_Character()
{
}

void DBG_Character::selectSkill(void)
{
	log().entranceFunction(FUNCTION_NAME);
	log() << "m_skill_index : " << m_skill_index << "\n";
	m_current_skill = m_skills[m_skill_index].get();
	m_skill_index++;
	if (m_skill_index >= m_skills.size())
		m_skill_index = 0;
	m_targets.push_back(m_ennemies.front());
	log().exitFunction();
}

void DBG_Character::useSkill(void)
{
	log().entranceFunction(FUNCTION_NAME);

	if (!isDead())
	{
		m_current_skill->use(m_targets);
	}
	m_targets.resize(0);
	log().exitFunction();
}

int DBG_Character::getBaseAttack(void) const
{
	return 5;
}

bool DBG_Character::loadSkills(const SkillManager& sm)
{
	bool l_ret(false);

	m_skills.resize(0);

	//m_skills[0].reset(sm.getSkill("skill test ADD", *this));

	return l_ret;
}

void DBG_Character::setDamages(int hp_damages)
{
	log().entranceFunction(FUNCTION_NAME);
	log() << m_name << "::setDamages\n";
	log() << "\t" << hp_damages << " hp lost\n";
	m_hp -= hp_damages;
	log() << "\t" << m_hp.m_actual_value << " hp remaining\n";
	log().exitFunction();
}

