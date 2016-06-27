#ifndef _ICHARACTER_HPP
#define _ICHARACTER_HPP 1

#include <vector>

class ICharacter
{
public:
	virtual ~ICharacter() {}

	virtual int getBaseAttack(void) const = 0;
	virtual void setDamages(int hp_damages) = 0;

	/** Init methods **/
	virtual void setEnnemies(const std::vector<ICharacter*>& ennemies) = 0;

	/** Fight methods **/
	virtual void selectSkill(void) = 0;
	virtual void useSkill(void) = 0;

	/** States methods **/
	virtual bool isDead(void) const = 0;
};

#endif // !_ICHARACTER_HPP