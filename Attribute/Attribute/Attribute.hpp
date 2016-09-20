#ifndef _ATTRIBUTE_HPP
#define _ATTRIBUTE_HPP 1

#include "Attribute/IAttribute.hpp"

class Attribute : public IAttribute
{
public:
	Attribute(const std::string& name);
	virtual ~Attribute();
	virtual const std::string& getName(void);

protected:
	std::string m_name;
};

#endif // _ATTRIBUTE_HPP
