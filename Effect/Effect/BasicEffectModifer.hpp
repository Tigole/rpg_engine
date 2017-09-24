#ifndef _BASIC_EFFECT_MODIFER_HPP
#define _BASIC_EFFECT_MODIFER_HPP 1

#include "Effect.hpp"

class BasicEffectModifier : public Effect
{
public:
	BasicEffectModifier(const std::string& target_attribute, const std::string& formula);

	virtual void mt_Affect(ISkill& skill_owner, ICharacter& char_owner, ICharacter& char_target);

	std::unique_ptr<IEffect> mt_Clone(void) const;

private:
	std::string m_formula;

};

#endif // !_BASIC_EFFECT_MODIFER_HPP
