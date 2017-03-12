#include "BasicEffectSetter.hpp"

#include "Character/ICharacter.hpp"
#include "Math/VariableList.hpp"
#include "Math/ExpressionParser.hpp"
#include "Exception/Exception.hpp"


BasicEffectSetter::BasicEffectSetter(const std::string& target_attribute, const std::string& formula)
	:m_target_attribute(target_attribute),
	m_formula(formula)
{
	/** Nothing **/
}

void BasicEffectSetter::affect(ISkill& skill_owner, ICharacter& char_owner, ICharacter& char_target)
{
	bool l_ret(true);
	std::vector<std::string> var_names;
	VariableList var_list;
	ExpressionParser<int> parser;
	int attribute_value;
	std::string affected_name, affected_attribute;

	getVariables(m_formula, var_names);

	getVariables(skill_owner, char_owner, char_target, var_names, var_list);

	if (parser.parse(m_formula, var_list) == false)
		throw Exception("\"parser.parse(" + m_formula + ", var_list) == false\"");

	if (parser.getResult(attribute_value) == false)
		throw Exception("Failed when getting result in \"" + std::string(FUNCTION_NAME) + "\"");

	splitNameAndAttribute(m_target_attribute, affected_name, affected_attribute);

	if (affected_name == "skill")
		affect(skill_owner, affected_attribute, attribute_value);
	else if (affected_name == "owner")
		affect(char_owner, affected_attribute, attribute_value);
	else if (affected_name == "target")
		affect(char_target, affected_attribute, attribute_value);
	else
		throw ExceptionResourceDoesNotExists(affected_name, FUNCTION_NAME);
}

std::unique_ptr<IEffect> BasicEffectSetter::clone(void) const
{
	return std::unique_ptr<IEffect>(new BasicEffectSetter(*this));
}

void BasicEffectSetter::getVariables(const std::string& formula, std::vector<std::string>& variables)
{
	std::string current_variable;
	std::vector<char> c;

	c.push_back('+');
	c.push_back('-');
	c.push_back('^');
	c.push_back('*');
	c.push_back('/');
	c.push_back('(');
	c.push_back(')');
	c.push_back(' ');
	c.push_back('\t');
	c.push_back('\n');
	c.push_back('\r');
	c.push_back('\b');

	/** Retrieve var names **/
	for (unsigned int i = 0; i < m_formula.size(); i++)
	{
		if ((m_formula[i] < '0')
			|| (m_formula[i] > '9')
			|| (std::find(c.begin(), c.end(), m_formula[i]) == c.end()))
		{
			/** It's a valid character for a variable name **/
			current_variable.push_back(m_formula[i]);
		}
		else if (current_variable.size() != 0)
		{
			variables.push_back(current_variable);
			current_variable.resize(0);
		}
	}
}

void BasicEffectSetter::splitNameAndAttribute(const std::string& str, std::string& name, std::string& attribute)
{
	bool l_ret(false);
	std::string::size_type dot_pos;

	dot_pos = str.find('.');
	if (dot_pos == std::string::npos)
		throw ExceptionStringSplittingFail(str);

	name = str.substr(0, dot_pos);
	attribute = str.substr(dot_pos + 1);
}

void BasicEffectSetter::getVariables(ISkill& skill_owner, ICharacter& char_owner, ICharacter& char_target, const std::vector<std::string>& variables_names, VariableList& var_list)
{
	std::string formula_target_name, formula_target_attribute;
	int attribute_value;

	for (unsigned int i = 0; i < variables_names.size(); i++)
	{
		splitNameAndAttribute(variables_names[i], formula_target_name, formula_target_attribute);

		if (formula_target_name == "skill")
			getValue(skill_owner, formula_target_attribute, attribute_value);
		else if (formula_target_name == "owner")
			getValue(char_owner, formula_target_attribute, attribute_value);
		else if (formula_target_name == "target")
			getValue(char_target, formula_target_attribute, attribute_value);
		else
			throw ExceptionResourceDoesNotExists(formula_target_name, FUNCTION_NAME);

		var_list.setVariable(variables_names[i], misc::numberToString(attribute_value));
	}
}



