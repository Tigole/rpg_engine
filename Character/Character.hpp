#ifndef _CHARACTER_HPP
#define _CHARACTER_HPP 1

#include "BasicCharacter.hpp"

class Character : public BasicCharacter
{
public:
	Character(const std::string& name, int hp);
	virtual void selectSkill(void);
	virtual void useSkill(void);

protected:
	void chooseTarget(void);
	

	std::vector<ICharacter*> m_fighters;

};

#endif // !_CHARACTER_HPP
