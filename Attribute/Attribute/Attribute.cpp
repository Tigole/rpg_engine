#include "Attribute.hpp"

Attribute::Attribute(const std::string& name)
	:m_name(name)
{
	/** Nothing **/
}

Attribute::~Attribute()
{
	/** Nothing **/
}

const std::string& Attribute::getName(void)
{
	return m_name;
}