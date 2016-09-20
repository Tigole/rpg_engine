#ifndef _CHARACTER_BASIC_ATTRIBUTE_HPP
#define _CHARACTER_BASIC_ATTRIBUTE_HPP 1

#include "CharacterAttribute.hpp"
#include "BasicAttribute.hpp"

class CharacterBasicAttribute : public ICharacterAttribute, public BasicAttribute
{
public:
	CharacterBasicAttribute(const std::string& name);
	void startTurn(void);
	void endTurn(void);
	void endFight(void);
};

#endif // !_CHARACTER_BASIC_ATTRIBUTE_HPP