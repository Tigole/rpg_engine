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
		DSO_RAW,
		DSO_ERROR
	};

	static DamageSkillOperator mt_String_To_Operator(const std::string& op);

	DamageSkill(const std::string& name, int damages, DamageSkillOperator op);
	~DamageSkill();

protected:
	int mt_Affect_Character(ICharacter& target);

	virtual int mt_Manage_DSO_ADD(int owner_base_damages, int skill_damages) = 0;
	virtual int mt_Manage_DSO_MINUS(int owner_base_damages, int skill_damages) = 0;
	virtual int mt_Manage_DSO_MULTIPLY(int owner_base_damages, int skill_damages) = 0;
	virtual int mt_Manage_DSO_DIVIDE(int owner_base_damages, int skill_damages) = 0;
	virtual int mt_Manage_DSO_PERCENT(int owner_base_damages, int skill_damages) = 0;
	virtual int mt_Manage_DSO_RAW(int owner_base_damages, int skill_damages) = 0;

	static std::map<DamageSkillOperator, int (DamageSkill::*)(int, int)> m_operator_map;

	int m_damages;
	DamageSkillOperator m_operator;
};

#endif // !_DAMAGE_SKILL_HPP
