#include "DamageSkill.hpp"

#include "Character/ICharacter.hpp"
#include "Logger/ILogger.h"

#include <cassert>

std::map<DamageSkill::DamageSkillOperator, int (DamageSkill::*)(int, int)> DamageSkill::m_operator_map;

DamageSkill::DamageSkillOperator DamageSkill::stringToOperator(const std::string& op)
{
	DamageSkill::DamageSkillOperator l_ret(DSO_ERROR);
	std::map<std::string, DamageSkillOperator> l_map;
	std::map<std::string, DamageSkillOperator>::iterator l_map_it;

	l_map["DSO_ADD"] = DSO_ADD;
	l_map["DSO_MINUS"] = DSO_MINUS;
	l_map["DSO_MULTIPLY"] = DSO_MULTIPLY;
	l_map["DSO_DIVIDE"] = DSO_DIVIDE;
	l_map["DSO_PERCENT"] = DSO_PERCENT;
	l_map["DSO_RAW"] = DSO_RAW;

	l_map_it = l_map.find(op);
	if (l_map_it != l_map.end())
		l_ret = l_map_it->second;

	return l_ret;
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

int DamageSkill::affectCharacter(ICharacter& target)
{
	int damages;
	int tmp;
	auto it(m_operator_map.find(m_operator));
	ICharacterAttribute* attribute(nullptr);

	log().entranceFunction(FUNCTION_NAME);

	assert(it != m_operator_map.end());

	attribute = m_owner->getAttribute("attack");

	assert(attribute != nullptr);
	assert(attribute->getValue("attack", tmp) == true);

	log() << "name : " << m_id << "\n";
	log() << "m_owner->getAttribute(\"attack\", tmp) : " << tmp << "\n";
	log() << "m_damages : " << m_damages << "\n";

	damages = (this->*(it->second))(tmp, m_damages);

	log() << "damages : " << damages << "\n";

	attribute = target.getAttribute("hp");
	assert(attribute != nullptr);
	assert(attribute->getValue("hp", tmp) == true);

	tmp -= damages;

	attribute = target.getAttribute("hp");
	assert(attribute != nullptr);
	assert(attribute->getValue("hp", tmp));


	log().exitFunction();

	return damages;
}
