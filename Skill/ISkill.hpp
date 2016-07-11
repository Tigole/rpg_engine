#ifndef _ISKILL_HPP
#define _ISKILL_HPP 1

#include <vector>
#include "Miscellaneous.hpp"

class ICharacter;

class ISkill : public misc::Clonable<ISkill>
{
public:
	virtual ~ISkill(){}

	virtual void use(const std::vector<ICharacter*>& targets) = 0;
	virtual void setOwner(ICharacter& owner) = 0;
	virtual const std::string& getName(void) const = 0	;
};

#endif // !_ISKILL_HPP
