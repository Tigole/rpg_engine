#ifndef _DBG_DAMAGE_SKILL_HPP
#define _DBG_DAMAGE_SKILL_HPP 1

#include "DamageSkill.hpp"

extern "C"
{
	void fn_DeleteDBG_DamageSkill(ISkill* obj);
}

class DBG_DamageSkill : public DamageSkill
{
public:
	DBG_DamageSkill(const std::string& name, int damages, DamageSkillOperator op);

	std::unique_ptr<ISkill> mt_Clone(void) const;

protected:
	virtual int mt_Manage_DSO_ADD(int owner_base_damages, int skill_damages);
	virtual int mt_Manage_DSO_MINUS(int owner_base_damages, int skill_damages);
	virtual int mt_Manage_DSO_MULTIPLY(int owner_base_damages, int skill_damages);
	virtual int mt_Manage_DSO_DIVIDE(int owner_base_damages, int skill_damages);
	virtual int mt_Manage_DSO_PERCENT(int owner_base_damages, int skill_damages);
	virtual int mt_Manage_DSO_RAW(int owner_base_damages, int skill_damages);
};

#endif // _DBG_DAMAGE_SKILL_HPP
