#include "DBG_Character.hpp"
#include "Logger/ILogger.h"

#include "Skill/Skill/DamageSkill.hpp"

#include "Skill/SkillManager.hpp"
#include "Skill/ISkill.hpp"

DBG_Character::DBG_Character(const std::string& name, int hp_max)
	:BasicCharacter(name, misc::Gauge<int>(hp_max)),
	m_skill_index(0)
{
	/** Nothing **/
}

DBG_Character::~DBG_Character()
{
	/** Nothing **/
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

void DBG_Character::setDamages(int hp_damages)
{
	log().entranceFunction(FUNCTION_NAME);
	log() << m_name << "::setDamages\n";
	log() << "\t" << hp_damages << " hp lost\n";
	m_hp -= hp_damages;
	log() << "\t" << m_hp.m_actual_value << " hp remaining\n";
	log().exitFunction();
}

std::unique_ptr<ICharacter> DBG_Character::clone(void) const
{
	return std::unique_ptr<ICharacter>(new DBG_Character(*this));
}
