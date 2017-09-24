#ifndef _CHARACTER_BASIC_ATTRIBUTE_HPP
#define _CHARACTER_BASIC_ATTRIBUTE_HPP 1

#include "CharacterAttribute.hpp"
#include "BasicAttribute.hpp"

class CharacterBasicAttribute : public ICharacterAttribute, public BasicAttribute
{
public:
	CharacterBasicAttribute(const std::string& name);
	void mt_Start_Turn(void);
	void mt_End_Turn(void);
	void mt_End_Fight(void);
};

#endif // !_CHARACTER_BASIC_ATTRIBUTE_HPP
