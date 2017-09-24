#include "CompositeAttribute.hpp"
#include "Logger/ILogger.h"
#include "Exception/Exception.hpp"

#include <algorithm>

void deleteCompositeAttribute(IAttribute* obj)
{
	delete obj;
}

CompositeAttribute::CompositeAttribute(const std::string& base_name)
	:Attribute(base_name),
	m_attributes()
{
	/** Nothing **/
}
CompositeAttribute::CompositeAttribute(const CompositeAttribute& cp)
	: Attribute(cp),
	m_attributes()
{
	for (const auto& p : cp.m_attributes)
		m_attributes[p.first] = std::move(p.second->mt_Clone());
}

std::unique_ptr<IAttribute> CompositeAttribute::mt_Clone(void) const
{
	return std::unique_ptr<IAttribute>(new CompositeAttribute(*this));
}

void CompositeAttribute::mt_Save(TiXmlElement& parent) const
{
	TiXmlElement* l_this(nullptr);

	throw ExceptionUnimplementedFunction(FUNCTION_NAME);

	l_this = new TiXmlElement("CompositeAttribute");
		l_this->SetAttribute("name", m_name);
		for (auto it = m_attributes.begin(); it != m_attributes.end(); it++)
		{
			it->second->mt_Save(*l_this);
				log().mt_Entrance_Function(FUNCTION_NAME);
				log() << "Error while saving attribute \"" << it->first << "\"\n";
				log().mt_Exit_Function();
		}
}

void CompositeAttribute::mt_Add_Attributes(std::unique_ptr<IAttribute>& lower_attribute)
{
	bool l_ret(false);

	if (lower_attribute == nullptr)
		throw std::runtime_error(FUNCTION_NAME);

	if (m_attributes.find(lower_attribute->mt_Get_Name()) != m_attributes.end())
		throw ExceptionResourceAlradeyExists(lower_attribute->mt_Get_Name(), FUNCTION_NAME);

	m_attributes[lower_attribute->mt_Get_Name()] = std::move(lower_attribute);
}

void CompositeAttribute::mt_Get_Value(const std::string& attribute_name, int& value) const
{
	std::string base_name, lower_name;
	std::map<std::string, std::unique_ptr<IAttribute>>::const_iterator it;

	mt_Split_Attribute_Name(attribute_name, base_name, lower_name);

	if (base_name != m_name)
		throw ExceptionResourceDoesNotExists(base_name, FUNCTION_NAME);

	it = m_attributes.find(lower_name);
	if (it == m_attributes.end())
		throw ExceptionResourceDoesNotExists(lower_name, FUNCTION_NAME);

	it->second->mt_Get_Value(lower_name, value);
}

void CompositeAttribute::mt_Set_Value(const std::string& attribute_name, int value)
{
	std::string base_name, lower_name;
	std::map<std::string, std::unique_ptr<IAttribute>>::const_iterator it;

	mt_Split_Attribute_Name(attribute_name, base_name, lower_name);

	if (base_name != m_name)
		throw ExceptionResourceDoesNotExists(base_name, FUNCTION_NAME);

	it = m_attributes.find(lower_name);
	if (it == m_attributes.end())
		throw ExceptionResourceDoesNotExists(lower_name, FUNCTION_NAME);

	it->second->mt_Set_Value(lower_name, value);
}

void CompositeAttribute::mt_Split_Attribute_Name(const std::string& full_name, std::string& base_name, std::string& lower_name) const
{
	std::stringstream ss;

	if (full_name.find('.') == std::string::npos)
		throw ExceptionStringSplittingFail(full_name);

	ss.str(full_name);
	std::getline(ss, base_name, '.');
	ss >> lower_name;

	if (base_name.size() == 0 || lower_name.size() == 0)
		throw ExceptionStringSplittingFail(full_name);
}

void CompositeAttribute::mt_Dump(ILogger& l)
{
	l << "name : \"" << m_name << "\"\n";
	l.mt_Start_Block("children attributes");
	for (auto& a : m_attributes)
		a.second->mt_Dump(l);
	l.mt_End_Block();
}
