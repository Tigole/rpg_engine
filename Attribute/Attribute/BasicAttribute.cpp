#include "Attribute/Attribute/BasicAttribute.hpp"
#include "Attribute\Loader\BasicAttributeLoader.hpp"
#include "Logger\ILogger.h"

void deleteBasicAttribute(IAttribute* obj)
{
	delete obj;
}

BasicAttribute::BasicAttribute(const std::string& name, int value)
 :	Attribute(name),
	m_value(value)
{
	/** Nothing **/
}

BasicAttribute::BasicAttribute(const std::string& name)
 :	Attribute(name),
	m_value(0)
{
	/** Nothing **/
}

std::unique_ptr<IAttribute> BasicAttribute::clone(void) const
{
	return std::unique_ptr<IAttribute>(new BasicAttribute(*this));
}

bool BasicAttribute::save(TiXmlElement& parent) const
{
	bool l_ret(true);
	TiXmlElement* l_this(nullptr);

	l_this = new TiXmlElement("BasicAttribute");
	l_ret = (l_this != nullptr);
	if (l_ret == true)
	{
		l_this->SetAttribute("name", m_name);
		l_this->SetAttribute("value", m_value);
		parent.LinkEndChild(l_this);
	}

	return l_ret;
}

bool BasicAttribute::getValue(const std::string& attribute_name, int& value) const
{
	bool l_ret(false);

	l_ret = (attribute_name == m_name);
	if (l_ret == true)
		value = m_value;

	return l_ret;
}

bool BasicAttribute::setValue(const std::string& attribute_name, int value)
{
	bool l_ret(false);

	l_ret = (attribute_name == m_name);
	if (l_ret == true)
		m_value = value;

	return l_ret;
}

void BasicAttribute::dump(ILogger& l)
{
	l << "name : \"" << m_name << "\"\n";
	l << "value : \"" << m_value << "\"\n";
}