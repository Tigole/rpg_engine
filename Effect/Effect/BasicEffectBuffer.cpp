#include "BasicEffectBuffer.hpp"

#include "Exception/Exception.hpp"

BasicEffectBuffer::BasicEffectBuffer(const std::string& target_attribute, int value, int nb_turn)
	:Effect(target_attribute),
	m_value(value),
	m_nb_turn(nb_turn)
{
	/** Nothing **/
}

void BasicEffectBuffer::affect(ISkill& skill_owner, ICharacter& char_owner, ICharacter& char_target)
{
	throw UnimplementedFunction(FUNCTION_NAME);
}

std::unique_ptr<IEffect> BasicEffectBuffer::clone(void) const
{
	return std::unique_ptr<IEffect>(new BasicEffectBuffer(*this));
}

