#include "BasicEffectModifer.hpp"
#include "Exception/Exception.hpp"

BasicEffectModifier::BasicEffectModifier(const std::string& target_attribute, const std::string& formula)
	:Effect(target_attribute),
	m_formula(formula)
{
	/** Nothing **/
}

void BasicEffectModifier::mt_Affect(ISkill& skill_owner, ICharacter& char_owner, ICharacter& char_target)
{
	throw ExceptionUnimplementedFunction(FUNCTION_NAME);
}
std::unique_ptr<IEffect> BasicEffectModifier::mt_Clone(void) const
{
	return std::unique_ptr<IEffect>(new BasicEffectModifier(*this));
}

