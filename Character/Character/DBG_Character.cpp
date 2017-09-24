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

void DBG_Character::mt_Start_Turn(void)
{
	/** Nothing **/
}

void DBG_Character::mt_End_Turn(void)
{
	/** Nothing **/
}

void DBG_Character::mt_Select_Skill(void)
{
	log().mt_Entrance_Function(FUNCTION_NAME);
	log() << "m_skill_index : " << m_skill_index << "\n";
	m_current_skill = m_skills[m_skill_index].get();
	m_skill_index++;
	if (m_skill_index >= m_skills.size())
		m_skill_index = 0;
	m_targets.push_back(m_ennemies.front());
	log().mt_Exit_Function();
}

void DBG_Character::mt_Use_Skill(void)
{
	log().mt_Entrance_Function(FUNCTION_NAME);

	if (!mt_Is_Dead())
	{
		//m_current_skill->use(m_targets);
	}
	m_targets.resize(0);
	log().mt_Exit_Function();
}

bool DBG_Character::mt_Is_Dead(void) const
{
	bool l_ret(false);
	int hp;

	mt_Get_Attribute("hp", hp);

	assert(l_ret == true);

	l_ret = (hp <= 0);

	return l_ret;
}

std::unique_ptr<ICharacter> DBG_Character::mt_Clone(void) const
{
	return std::unique_ptr<ICharacter>(new DBG_Character(m_name, 5));
}
