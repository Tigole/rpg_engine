#ifndef _ICHARACTER_ATTRIBUTE_HPP
#define _ICHARACTER_ATTRIBUTE_HPP 1

#include "Miscellaneous.hpp"

class ICharacterAttribute : public misc::Clonable<ICharacterAttribute>
{
public:
	ICharacterAttribute(){}
	virtual ~ICharacterAttribute(){}
	virtual void startTurn(void) = 0;
	virtual void endTurn(void) = 0;
	virtual void endFight(void) = 0;

	virtual const std::string& getName(void) const = 0;
	virtual bool getValue(const std::string& attribute_name, int& value) const = 0;
	virtual bool setValue(const std::string& attribute_name, int value) = 0;
	virtual bool save(TiXmlElement& parent) const = 0;
	virtual void dump(ILogger& l) = 0;
};

#endif // !_ICHARACTER_ATTRIBUTE_HPP