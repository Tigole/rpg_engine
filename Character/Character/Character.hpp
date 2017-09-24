#ifndef _CHARACTER_HPP
#define _CHARACTER_HPP 1

#include "BasicCharacter.hpp"

class Character : public BasicCharacter
{
public:
	Character(const std::string& name, int hp);
	virtual void mt_Select_Skill(void);
	virtual void mt_Use_Skill(void);

protected:
	void mt_Choose_Target(void);


	std::vector<ICharacter*> m_fighters;

};

#endif // !_CHARACTER_HPP
