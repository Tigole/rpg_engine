#ifndef _DAMAGE_SKILL_HPP
#define _DAMAGE_SKILL_HPP 1

#include "BasicSkill.hpp"

#include <map>

class DamageSkill : public BasicSkill
{
public:
	enum DamageSkillOperator
	{
		DSO_ADD,
		DSO_MINUS,
		DSO_MULTIPLY,
		DSO_DIVIDE,
		DSO_PERCENT,
		DSO_RAW
	};

	static DamageSkillOperator stringToOperator(const std::string& op);

	DamageSkill(const std::string& name, int damages, DamageSkillOperator op);
	~DamageSkill();

	DamageSkill* clone(void) const;

protected:
	int affectCharacter(ICharacter& target);

	int manage_DSO_ADD(int owner_base_damages, int skill_damages);
	int manage_DSO_MINUS(int owner_base_damages, int skill_damages);
	int manage_DSO_MULTIPLY(int owner_base_damages, int skill_damages);
	int manage_DSO_DIVIDE(int owner_base_damages, int skill_damages);
	int manage_DSO_PERCENT(int owner_base_damages, int skill_damages);
	int manage_DSO_RAW(int owner_base_damages, int skill_damages);

	static std::map<DamageSkillOperator, int (DamageSkill::*)(int, int)> m_operator_map;

	int m_damages;
	DamageSkillOperator m_operator;
};

#endif // !_DAMAGE_SKILL_HPP
