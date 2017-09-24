#include "CharacterAttribute.hpp"
#include "Logger/ILogger.h"

CharacterAttribute::CharacterAttribute(const std::string& name)
	:m_name(name)
{
	/** Nothing **/
}

CharacterAttribute::~CharacterAttribute()
{
	/** Nothing **/
}

const std::string& CharacterAttribute::mt_Get_Name(void) const
{
	return m_name;
}

void CharacterAttribute::mt_Dump(ILogger& l)
{
	l << "name : \"" << m_name << "\"\n";
}
