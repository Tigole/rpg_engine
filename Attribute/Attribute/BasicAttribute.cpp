#include "Attribute/Attribute/BasicAttribute.hpp"
#include "Attribute/Loader/BasicAttributeLoader.hpp"
#include "Logger/ILogger.h"
#include "Exception/Exception.hpp"

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

std::unique_ptr<IAttribute> BasicAttribute::mt_Clone(void) const
{
	return std::unique_ptr<IAttribute>(new BasicAttribute(*this));
}

void BasicAttribute::mt_Save(TiXmlElement& parent) const
{
	TiXmlElement* l_this(nullptr);

	l_this = new TiXmlElement("BasicAttribute");

	l_this->SetAttribute("name", m_name);
	l_this->SetAttribute("value", m_value);
	parent.LinkEndChild(l_this);
}

void BasicAttribute::mt_Get_Value(const std::string& attribute_name, int& value) const
{
	if (attribute_name != m_name)
		throw ExceptionAttributeNotFound(attribute_name, "BasicAttribute");

	value = m_value;
}

void BasicAttribute::mt_Set_Value(const std::string& attribute_name, int value)
{
	if (attribute_name != m_name)
		throw ExceptionAttributeNotFound(attribute_name, "BasicAttribute");

	m_value = value;
}

void BasicAttribute::mt_Dump(ILogger& l)
{
	l << "name : \"" << m_name << "\"\n";
	l << "value : \"" << m_value << "\"\n";
}
