#ifndef _BASIC_SKILL_HPP
#define _BASIC_SKILL_HPP 1

#include "Skill/ISkill.hpp"
#include "Math/VariableList.hpp"

#include <string>

extern "C"
{
	void fn_Delete_BasicSkill(ISkill* obj);
}

class IEffect;

class BasicSkill : public ISkill
{
public:
	BasicSkill(const std::string& id);
	BasicSkill(const BasicSkill& bs);
	virtual ~BasicSkill();
	BasicSkill& operator=(const BasicSkill& bs);

	virtual void mt_Use(const std::vector<IBattleGroundWrapper*>& targets);
	virtual void mt_Set_Owner(ICharacter& owner);
	virtual const std::string& mt_Get_Name(void) const;
	void mt_Add_Effect(const std::unique_ptr<IEffect>& effect);

	std::unique_ptr<ISkill> mt_Clone(void) const;

protected:
	ICharacter* m_owner;
	std::string m_id;
	std::vector<std::unique_ptr<IEffect>> m_effects;
};

#endif // !_BASIC_SKILL_HPP
