#ifndef _BASIC_SKILL_HPP
#define _BASIC_SKILL_HPP 1

#include "Skill/ISkill.hpp"
#include "Math/VariableList.hpp"

#include <string>

extern "C"
{
	void deleteBasicSkill(ISkill* obj);
}

class IEffect;

class BasicSkill : public ISkill
{
public:
	BasicSkill(const std::string& id);
	BasicSkill(const BasicSkill& bs);
	virtual ~BasicSkill();
	BasicSkill& operator=(const BasicSkill& bs);

	virtual void use(const std::vector<IBattleGroundWrapper*>& targets);
	virtual void setOwner(ICharacter& owner);
	virtual const std::string& getName(void) const;
	void addEffect(const std::unique_ptr<IEffect>& effect);

	std::unique_ptr<ISkill> clone(void) const;

protected:

	/*virtual int affectCharacter(ICharacter& target);

	bool getVariablesFromFormula(ICharacter& target, VariableList& vars);
	bool evaluateFormula(ICharacter& target, int& result);*/

	ICharacter* m_owner;
	std::string m_id;
	std::vector<std::unique_ptr<IEffect>> m_effects;
	//std::string m_formula;
	//std::string m_target_attribute;
};

#endif // !_BASIC_SKILL_HPP
