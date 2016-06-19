#ifndef _ICHARACTER_HPP
#define _ICHARACTER_HPP 1

#include <vector>

class ICharacter
{
public:
	virtual ~ICharacter() {}

	virtual bool isDead(void) const = 0;
	virtual void selectSkill(void) = 0;
	virtual void useSkill(void) = 0;
	virtual void setDamages(int hp_damages) = 0;
	virtual void setEnnemies(const std::vector<ICharacter*>& ennemies) = 0;
};

#endif // !_ICHARACTER_HPP