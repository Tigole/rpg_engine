#ifndef _ICHARACTER_ATTRIBUTE_HPP
#define _ICHARACTER_ATTRIBUTE_HPP 1

#include "Miscellaneous.hpp"

class ICharacterAttribute : public misc::Clonable<ICharacterAttribute>
{
public:
	ICharacterAttribute(){}
	virtual ~ICharacterAttribute(){}
	virtual void mt_Start_Turn(void) = 0;
	virtual void mt_End_Turn(void) = 0;
	virtual void mt_End_Fight(void) = 0;

	virtual const std::string& mt_Get_Name(void) const = 0;
	virtual bool mt_Get_Value(const std::string& attribute_name, int& value) const = 0;
	virtual bool mt_Set_Value(const std::string& attribute_name, int value) = 0;
	virtual bool mt_Save(TiXmlElement& parent) const = 0;
	virtual void mt_Dump(ILogger& l) = 0;
};

#endif // !_ICHARACTER_ATTRIBUTE_HPP
