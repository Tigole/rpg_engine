#include "DBG_DamageSkill.hpp"

DBG_DamageSkill::DBG_DamageSkill(const std::string& name, int damages, DamageSkill::DamageSkillOperator op)
 :	DamageSkill(name, damages, op)
{
	/** Nothing **/
}

int DBG_DamageSkill::manage_DSO_ADD(int owner_base_damages, int skill_damages)
{
	return owner_base_damages + skill_damages;
}

int DBG_DamageSkill::manage_DSO_MINUS(int owner_base_damages, int skill_damages)
{
	return owner_base_damages - skill_damages;
}

int DBG_DamageSkill::manage_DSO_PERCENT(int owner_base_damages, int skill_damages)
{
	return (owner_base_damages * skill_damages) / 100;
}

int DBG_DamageSkill::manage_DSO_RAW(int owner_base_damages, int skill_damages)
{
    UNUSED_PARAMETER(owner_base_damages);
	return skill_damages;
}

int DBG_DamageSkill::manage_DSO_MULTIPLY(int owner_base_damages, int skill_damages)
{
	return owner_base_damages * skill_damages;
}

int DBG_DamageSkill::manage_DSO_DIVIDE(int owner_base_damages, int skill_damages)
{
	assert(skill_damages != 0);
	return owner_base_damages / skill_damages;
}

std::unique_ptr<ISkill> DBG_DamageSkill::clone(void) const
{
	return std::unique_ptr<ISkill>(new DBG_DamageSkill(*this));
}

