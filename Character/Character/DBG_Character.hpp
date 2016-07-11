#ifndef _DBG_CHARACTER_HPP
#define _DBG_CHARACTER_HPP 1

#include "Character/ICharacter.hpp"
#include "BasicCharacter.hpp"

class SkillManager;

class DBG_Character : public BasicCharacter
{
public:
	DBG_Character(const std::string& name, int hp_max);
	~DBG_Character();

	virtual void selectSkill(void);
	virtual void useSkill(void);
	virtual void setDamages(int hp_damages);
	virtual int getBaseAttack(void) const;

	std::unique_ptr<ICharacter> clone() const;

private:
	int m_skill_index;
};

#endif // !_DBG_CHARACTER_HPP