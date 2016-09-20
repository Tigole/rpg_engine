#include "DBG_Character.hpp"
#include "Logger/ILogger.h"

#include "Skill/Skill/DamageSkill.hpp"

#include "Skill/SkillManager.hpp"
#include "Skill/ISkill.hpp"

void deleteDBG_Character(ICharacter* obj)
{
	delete obj;
}

DBG_Character::DBG_Character(const std::string& name, int hp_max)
	:BasicCharacter(name),
	m_skill_index(0)
{
	/** Nothing **/
}

DBG_Character::~DBG_Character()
{
	/** Nothing **/
}

void DBG_Character::startTurn(void)
{
	/** Nothing **/
}

void DBG_Character::endTurn(void)
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
		//m_current_skill->use(m_targets);
	}
	m_targets.resize(0);
	log().exitFunction();
}

bool DBG_Character::isDead(void) const
{
	bool l_ret(false);
	int hp;

	l_ret = getAttribute("hp", hp);

	assert(l_ret == true);

	l_ret = (hp <= 0);

	return l_ret;
}

std::unique_ptr<ICharacter> DBG_Character::clone(void) const
{
	return std::unique_ptr<ICharacter>(new DBG_Character(m_name, 5));
}
