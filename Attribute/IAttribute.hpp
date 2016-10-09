#ifndef _IATTRIBUTE_HPP
#define _IATTRIBUTE_HPP 1

#include "Miscellaneous.hpp"

#include <string>

class IAttribute : public misc::Clonable<IAttribute>
{
public:
	virtual ~IAttribute(){}

	virtual const std::string& getName(void) = 0;
	virtual void getValue(const std::string& attribute_name, int& value) const = 0;
	virtual void setValue(const std::string& attribute_name, int value) = 0;
	virtual void save(TiXmlElement& parent) const = 0;
	virtual void dump(ILogger& l) = 0;

	/** \fn virtual const std::string& getName(void) = 0
		\brief Get the name of the attribute
	**/
	/** \fn bool getValue(const std::string& attribute_name, int& value) const
		\brief Get the value of the attribute
	**/
	/** \fn bool setValue(const std::string& attribute_name, int value)
		\brief Set the value of the attribute
	**/
};

#endif // _IATTRIBUTE_HPP
