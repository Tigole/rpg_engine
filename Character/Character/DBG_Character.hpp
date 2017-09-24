#ifndef _DBG_CHARACTER_HPP
#define _DBG_CHARACTER_HPP 1

#include "Character/ICharacter.hpp"
#include "BasicCharacter.hpp"

class SkillManager;

extern "C"
{
	void deleteDBG_Character(ICharacter* obj);
}

class DBG_Character : public BasicCharacter
{
public:
	DBG_Character(const std::string& name, int hp_max);
	~DBG_Character();

	virtual void mt_Start_Turn(void);
	virtual void mt_End_Turn(void);
	virtual void mt_Select_Skill(void);
	virtual void mt_Use_Skill(void);
	virtual bool mt_Is_Dead(void) const;

	std::unique_ptr<ICharacter> mt_Clone() const;

private:
	int m_skill_index;
};

#endif // !_DBG_CHARACTER_HPP
