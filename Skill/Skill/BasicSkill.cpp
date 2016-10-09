#include "BasicSkill.hpp"

#include "FSM/FSM.hpp"
#include "Attribute/IAttribute.hpp"
#include "Attribute/ICharacterised.hpp"
#include "Miscellaneous.hpp"
#include "Character/ICharacter.hpp"
#include "Logger/ILogger.h"
#include "Math\ExpressionParser.hpp"
#include "FightEngine\IBattleGroundWrapper.hpp"
#include "Effect\IEffect.hpp"

#include <algorithm>

void deleteBasicSkill(ISkill* obj)
{
	delete obj;
}

BasicSkill::BasicSkill(const std::string & id)
	:m_owner(nullptr),
	m_id(id)
{
	/** Nothing **/
}

BasicSkill::BasicSkill(const BasicSkill& bs)
 :	m_owner(nullptr),
	m_id(bs.m_id)
{
	for (auto& effect : bs.m_effects)
		m_effects.push_back(effect->clone());
}

BasicSkill::~BasicSkill()
{
	/** Nothing **/
}

BasicSkill& BasicSkill::operator=(const BasicSkill& bs)
{
	m_owner = bs.m_owner;
	m_id = bs.m_id;
	return *this;
}

std::unique_ptr<ISkill> BasicSkill::clone(void) const
{
	return std::unique_ptr<ISkill>(new BasicSkill(*this));
}

void BasicSkill::use(const std::vector<IBattleGroundWrapper*>& targets)
{
	ICharacter* t(nullptr);
	if (m_owner != nullptr)
		for (auto& target : targets)
		{
			t = target->getCharacter();
			if (t != nullptr)
				for (auto& effect : m_effects)
					effect->affect(*this, *m_owner, *t);
		};
}

void BasicSkill::setOwner(ICharacter& owner)
{
	m_owner = &owner;
}

const std::string& BasicSkill::getName(void) const
{
	return m_id;
}

void BasicSkill::addEffect(const std::unique_ptr<IEffect>& effect)
{
	m_effects.push_back(effect->clone());
}

#if 0
int BasicSkill::affectCharacter(ICharacter& target)
{
	int target_attribute_new_value(0);
	ICharacterAttribute* target_attribute(nullptr);

	target_attribute = target.getAttribute(m_target_attribute);

	if (target_attribute != nullptr)
	{
		if (evaluateFormula(target, target_attribute_new_value) == true)
		{
			target_attribute->setValue(m_target_attribute, target_attribute_new_value);
		}
		else
		{
			log().entranceFunction(FUNCTION_NAME);
			log() << "Formula evaluation failed\n";
			log().exitFunction();
		}
	}
	else
	{
		log().entranceFunction(FUNCTION_NAME);
		log() << "Getting attribute \"" << m_target_attribute << "\" from target failed\n";
		log().exitFunction();
	}

	return target_attribute_new_value;
}

bool BasicSkill::evaluateFormula(ICharacter& target, int& result)
{
	bool l_ret(false);
	ICharacterAttribute* target_attribute(nullptr);
	VariableList vars_list;
	ExpressionParser<int> parser;

	target_attribute = target.getAttribute(m_target_attribute);

	if (target_attribute != nullptr)
	{
		if (getVariablesFromFormula(target, vars_list) == true)
		{
			if (parser.parse(m_formula, vars_list) == true)
			{
				if (parser.getResult(result) == true)
				{
					l_ret = true;
				}
				else
				{
					log().entranceFunction(FUNCTION_NAME);
					log() << "Getting formula's result failed\n";
					log() << "Error: " << parser.getError() << "\n";
					log().exitFunction();
				}
			}
			else
			{
				log().entranceFunction(FUNCTION_NAME);
				log() << "Parsing formula failed\n";
				log() << "Error: " << parser.getError() << "\n";
				log().exitFunction();
			}
		}
		else
		{
			log().entranceFunction(FUNCTION_NAME);
			log() << "Getting variables from fomula failed\n";
			log().exitFunction();
		}
	}
	else
	{
		log().entranceFunction(FUNCTION_NAME);
		log() << "Getting attribute \"" << m_target_attribute << "\" from target failed\n";
		log().exitFunction();
	}

	return l_ret;
}

bool BasicSkill::getVariablesFromFormula(ICharacter& target, VariableList& vars)
{
	bool l_ret(true);
	std::string current_variable;
	std::vector<char> c;
	std::vector<std::string> var_names;
	std::string formula_target_name, formula_target_attribute;
	IAttribute* attribute(nullptr);
	ICharacterAttribute* character_attribute(nullptr);
	int attribute_value;
	std::map<std::string, ICharacterised*>::iterator it;

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
		if (	(m_formula[i] < '0')
			||	(m_formula[i] > '9')
			||	(std::find(c.begin(), c.end(), m_formula[i]) == c.end()))
		{
			/** It's a valid character for a variable name **/
			current_variable.push_back(m_formula[i]);
		}
		else if (current_variable.size() != 0)
		{
			var_names.push_back(current_variable);
			current_variable.resize(0);
		}
	}

	/** Retrieve var values **/
	for (unsigned int i = 0; (l_ret == true) && (i < var_names.size()); i++)
	{
		std::string::size_type dot_pos;

		dot_pos = var_names[i].find('.');
		if (dot_pos == std::string::npos)
		{
			log().entranceFunction(FUNCTION_NAME);
			log() << "Variable name is invalid (no '.'): \"" << var_names[i] << "\"\n";
			log().exitFunction();
			l_ret = false;
		}
		else
		{
			formula_target_name = var_names[i].substr(0, dot_pos);
			formula_target_attribute = var_names[i].substr(dot_pos + 1);

			if (formula_target_name != "skill")
			{
				if (formula_target_name == "target")
				{
					character_attribute = target.getAttribute(formula_target_attribute);
				}
				else if (formula_target_name == "owner")
				{
					character_attribute = m_owner->getAttribute(formula_target_attribute);
				}

				if (character_attribute != nullptr)
				{
					l_ret = character_attribute->getValue(formula_target_attribute, attribute_value);

					if (l_ret == false)
					{
						log().entranceFunction(FUNCTION_NAME);
						log() << "Couldn't get attribute \"" << formula_target_attribute << "\" from target \"" << formula_target_name << "\" (shouldn't happen!)";
						l_ret = false;
						log().exitFunction();
					}
				}
				else
				{
					log().entranceFunction(FUNCTION_NAME);
					log() << "Keyword \"" << formula_target_name << "\" in formula is not recognized by the object\n";
					log().startBlock("Recognized targets");
					log() << "target\n";
					log() << "owner\n";
					log() << "skill\n";
					log().endBlock();
					log().exitFunction();
					l_ret = false;
				}
			}
			else if (formula_target_name == "skill")
			{
				attribute = getAttribute(formula_target_attribute);

				if (attribute != nullptr)
				{
					l_ret = attribute->getValue(formula_target_attribute, attribute_value);

					if (l_ret == false)
					{
						log().entranceFunction(FUNCTION_NAME);
						log() << "Couldn't get attribute \"" << formula_target_attribute << "\" from target \"" << formula_target_name << "\" (shouldn't happen!)";
						l_ret = false;
						log().exitFunction();
					}
				}
			}
			else
			{
				log().entranceFunction(FUNCTION_NAME);
				log() << "Keyword \"" << formula_target_name << "\" in formula is not recognized by the object\n";
				log().startBlock("Recognized targets");
				log() << "target\n";
				log() << "owner\n";
				log() << "skill\n";
				log().endBlock();
				log().exitFunction();
				l_ret = false;
			}

			if (l_ret == true)
			{
				vars.setVariable(var_names[i], misc::numberToString(attribute_value));
			}
		}
	}

	return l_ret;
}

#endif
