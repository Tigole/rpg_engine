#include "DamageSkill.hpp"

#include "Character/ICharacter.hpp"
#include "Logger/ILogger.h"

#include <cassert>

std::map<DamageSkill::DamageSkillOperator, int (DamageSkill::*)(int, int)> DamageSkill::m_operator_map;

DamageSkill::DamageSkillOperator DamageSkill::stringToOperator(const std::string & op)
{
	std::map<std::string, DamageSkillOperator> l_map;
	std::map<std::string, DamageSkillOperator>::iterator l_map_it;

	l_map["DSO_ADD"] = DSO_ADD;
	l_map["DSO_MINUS"] = DSO_MINUS;
	l_map["DSO_MULTIPLY"] = DSO_MULTIPLY;
	l_map["DSO_DIVIDE"] = DSO_DIVIDE;
	l_map["DSO_PERCENT"] = DSO_PERCENT;
	l_map["DSO_RAW"] = DSO_RAW;

	l_map_it = l_map.find(op);

	assert(l_map_it != l_map.end());

	return l_map_it->second;
}

DamageSkill::DamageSkill(const std::string& name, int damages, DamageSkillOperator op)
	:BasicSkill(name),
	m_damages(damages),
	m_operator(op)
{
	if (m_operator_map.size() != 6)
	{
		m_operator_map[DSO_ADD] = &DamageSkill::manage_DSO_ADD;
		m_operator_map[DSO_MINUS] = &DamageSkill::manage_DSO_MINUS;
		m_operator_map[DSO_PERCENT] = &DamageSkill::manage_DSO_PERCENT;
		m_operator_map[DSO_RAW] = &DamageSkill::manage_DSO_RAW;
		m_operator_map[DSO_MULTIPLY] = &DamageSkill::manage_DSO_MULTIPLY;
		m_operator_map[DSO_DIVIDE] = &DamageSkill::manage_DSO_DIVIDE;
	}
}

DamageSkill::~DamageSkill()
{
	/** Nothing **/
}

DamageSkill* DamageSkill::clone(void) const
{
	return new DamageSkill(*this);
}

int DamageSkill::affectCharacter(ICharacter& target)
{
	int damages;
	auto it(m_operator_map.find(m_operator));

	log().entranceFunction(FUNCTION_NAME);

	assert(it != m_operator_map.end());

	log() << "name : " << m_name << "\n";
	log() << "m_owner.getBaseAttack() : " << m_owner->getBaseAttack() << "\n";
	log() << "m_damages : " << m_damages << "\n";

	damages = (this->*(it->second))(m_owner->getBaseAttack(), m_damages);

	log() << "damages : " << damages << "\n";

	target.setDamages(damages);

	log().exitFunction();

	return damages;
}

int DamageSkill::manage_DSO_ADD(int owner_base_damages, int skill_damages)
{
	return owner_base_damages + skill_damages;
}

int DamageSkill::manage_DSO_MINUS(int owner_base_damages, int skill_damages)
{
	return owner_base_damages - skill_damages;
}

int DamageSkill::manage_DSO_PERCENT(int owner_base_damages, int skill_damages)
{
	return (owner_base_damages * skill_damages) / 100;
}

int DamageSkill::manage_DSO_RAW(int owner_base_damages, int skill_damages)
{
    UNUSED_PARAMETER(owner_base_damages);
	return skill_damages;
}

int DamageSkill::manage_DSO_MULTIPLY(int owner_base_damages, int skill_damages)
{
	return owner_base_damages * skill_damages;
}

int DamageSkill::manage_DSO_DIVIDE(int owner_base_damages, int skill_damages)
{
	assert(skill_damages != 0);
	return owner_base_damages / skill_damages;
}
