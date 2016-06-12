#ifndef _DBG_CHARACTER_H
#define _DBG_CHARACTER_H 1

#include "ICharacter.hpp"

class DBG_Character : public ICharacter
{
public:
	DBG_Character(const char* name, int hp_max);
	~DBG_Character();

	virtual bool isDead(void) const;
	virtual void selectSkill(void) const;
	virtual void useSkill(ICharacter& target);
	int setDamages(int hp_damages);
private:
	int m_hp;
	const char* m_name;
};

#endif // !_DBG_CHARACTER_H