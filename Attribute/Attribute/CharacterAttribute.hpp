#ifndef _CHARACTER_ATTRIBUTE_HPP
#define _CHARACTER_ATTRIBUTE_HPP 1

#include "ICharacterAttribute.hpp"

class CharacterAttribute : public ICharacterAttribute
{
public:
	CharacterAttribute(const std::string& name);
	virtual ~CharacterAttribute();

	virtual const std::string& getName(void);
	virtual void dump(ILogger& l);

protected:
	std::string m_name;
};

#endif // _CHARACTER_ATTRIBUTE_HPP
