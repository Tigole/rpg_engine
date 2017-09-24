#ifndef _BASIC_EFFECT_SETTER_HPP
#define _BASIC_EFFECT_SETTER_HPP 1

#include "Effect/IEffect.hpp"
#include "Skill/ISkill.hpp"

#include <string>
#include <vector>

class VariableList;

class BasicEffectSetter : public IEffect
{
public:
	BasicEffectSetter(const std::string& target_attribute, const std::string& formula);

	void mt_Affect(ISkill& skill_owner, ICharacter& char_owner, ICharacter& char_target);
	std::unique_ptr<IEffect> mt_Clone(void) const;

private:

	void mt_Get_Variables(const std::string& formula, std::vector<std::string>& variables);
	void mt_Split_Name_And_Attribute(const std::string& str, std::string& name, std::string& attribute);
	void mt_Get_Variables(ISkill& skill_owner, ICharacter& char_owner, ICharacter& char_target, const std::vector<std::string>& variables_names, VariableList& var_list);

	template<typename T>
	void mt_Affect(T& target, const std::string& attribute_name, int value)
	{
		target.mt_Get_Attribute(attribute_name)->mt_Set_Value(attribute_name, value);
	}

	template<typename T>
	void mt_Get_Value(T& target, const std::string& attribute_name, int& value)
	{
		target.mt_Get_Attribute(attribute_name)->mt_Get_Value(attribute_name, value);
	}

	std::string m_target_attribute;
	std::string m_formula;
};

#endif // !_BASIC_EFFECT_SETTER_HPP
