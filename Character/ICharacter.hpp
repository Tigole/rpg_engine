#ifndef _ICHARACTER_H
#define _ICHARACTER_H 1

class ICharacter
{
public:
	virtual ~ICharacter() {}

	virtual bool isDead(void) const = 0;
	virtual void selectSkill(void) const = 0;
	virtual void useSkill(ICharacter& target) = 0;
	virtual int setDamages(int hp_damages) = 0;
};

#endif // !_ICHARACTER_H