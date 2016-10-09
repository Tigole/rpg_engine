#ifndef _BASIC_EFFECT_BUFFER_HPP
#define _BASIC_EFFECT_BUFFER_HPP 1

#include "Effect.hpp"
#include <string>

class BasicEffectBuffer : public Effect
{
public:
	BasicEffectBuffer(const std::string& target_attribute, int value, int nb_turn);

	void affect(ISkill& skill_owner, ICharacter& char_owner, ICharacter& char_target);
	std::unique_ptr<IEffect> clone(void) const;

private:
	int m_value;
	int m_nb_turn;
};

#endif // !_BASIC_EFFECT_BUFFER_HPP