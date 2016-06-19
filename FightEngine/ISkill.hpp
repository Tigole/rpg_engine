#ifndef _ISKILL_HPP
#define _ISKILL_HPP 1

#include <vector>

class ICharacter;

class ISkill
{
public:
	virtual ~ISkill(){}

	virtual int use(const std::vector<ICharacter*>& targets) = 0;
};

#endif // !_ISKILL_HPP
