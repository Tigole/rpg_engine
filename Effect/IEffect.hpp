#ifndef _IEFFECT_HPP
#define _IEFFECT_HPP 1

#include "Miscellaneous.hpp"

class ICharacter;
class ISkill;

class IEffect : public misc::Clonable<IEffect>
{
public:
	virtual ~IEffect(){}

	virtual void affect(ISkill& skill_owner, ICharacter& char_owner, ICharacter& char_target) = 0;
};

#endif // !_IEFFECT_HPP
