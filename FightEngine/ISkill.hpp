#ifndef _ISKILL_HPP
#define _ISKILL_HPP 1

#include <vector>
#include "Miscellaneous.hpp"

class ICharacter;

class ISkill : public misc::Clonable
{
public:
	virtual ~ISkill(){}

	virtual void use(const std::vector<ICharacter*>& targets) = 0;
	virtual void setOwner(ICharacter& owner) = 0;
	virtual ISkill* clone(void) const = 0;
};

#endif // !_ISKILL_HPP
