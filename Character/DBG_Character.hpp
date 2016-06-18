#ifndef _DBG_CHARACTER_HPP
#define _DBG_CHARACTER_HPP 1

#include "ICharacter.hpp"

class DBG_Character : public ICharacter
{
public:
	DBG_Character(const char* name, int hp_max);
	~DBG_Character();

	virtual bool isDead(void) const;
	virtual void selectSkill(void);
	virtual void useSkill(void);
	int setDamages(int hp_damages);
	virtual void setEnnemies(const std::vector<ICharacter*>& ennemies);

	friend int main(int, char**);
private:
	int m_hp;
	const char* m_name;
	ICharacter* m_target;
	std::vector<ICharacter*> m_ennemies;
};

#endif // !_DBG_CHARACTER_HPP