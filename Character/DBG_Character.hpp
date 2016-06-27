#ifndef _DBG_CHARACTER_HPP
#define _DBG_CHARACTER_HPP 1

#include "ICharacter.hpp"
#include "BasicCharacter.hpp"

class SkillManager;

class DBG_Character : public BasicCharacter
{
public:
	DBG_Character(const char* name, int hp_max);
	~DBG_Character();

	virtual void selectSkill(void);
	virtual void useSkill(void);
	virtual void setDamages(int hp_damages);
	virtual int getBaseAttack(void) const;

	bool loadSkills(const SkillManager& sm);

private:
	int m_skill_index;
};

#endif // !_DBG_CHARACTER_HPP