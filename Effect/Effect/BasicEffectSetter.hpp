#ifndef _BASIC_EFFECT_SETTER_HPP
#define _BASIC_EFFECT_SETTER_HPP 1

#include "Effect\IEffect.hpp"
#include "Skill\ISkill.hpp"

#include <string>
#include <vector>

class VariableList;

class BasicEffectSetter : public IEffect
{
public:
	BasicEffectSetter(const std::string& target_attribute, const std::string& formula);

	void affect(ISkill& skill_owner, ICharacter& char_owner, ICharacter& char_target);
	std::unique_ptr<IEffect> clone(void) const;

private:

	void getVariables(const std::string& formula, std::vector<std::string>& variables);
	void splitNameAndAttribute(const std::string& str, std::string& name, std::string& attribute);
	void getVariables(ISkill& skill_owner, ICharacter& char_owner, ICharacter& char_target, const std::vector<std::string>& variables_names, VariableList& var_list);
	
	template<typename T>
	void affect(T& target, const std::string& attribute_name, int value)
	{
		target.getAttribute(attribute_name)->setValue(attribute_name, value);
	}

	template<typename T>
	void getValue(T& target, const std::string& attribute_name, int& value)
	{
		target.getAttribute(attribute_name)->getValue(attribute_name, value);
	}

	std::string m_target_attribute;
	std::string m_formula;
};

#endif // !_BASIC_EFFECT_SETTER_HPP
