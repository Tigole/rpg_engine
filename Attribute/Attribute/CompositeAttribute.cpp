#include "CompositeAttribute.hpp"
#include "Logger\ILogger.h"
#include "Exception\Exception.hpp"

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
		m_attributes[p.first] = std::move(p.second->clone());
}

std::unique_ptr<IAttribute> CompositeAttribute::clone(void) const
{
	return std::unique_ptr<IAttribute>(new CompositeAttribute(*this));
}

void CompositeAttribute::save(TiXmlElement& parent) const
{
	TiXmlElement* l_this(nullptr);

	throw UnimplementedFunction(FUNCTION_NAME);

	l_this = new TiXmlElement("CompositeAttribute");
		l_this->SetAttribute("name", m_name);
		for (auto it = m_attributes.begin(); it != m_attributes.end(); it++)
		{
			it->second->save(*l_this);
				log().entranceFunction(FUNCTION_NAME);
				log() << "Error while saving attribute \"" << it->first << "\"\n";
				log().exitFunction();
		}
}

void CompositeAttribute::addAttributes(std::unique_ptr<IAttribute>& lower_attribute)
{
	bool l_ret(false);

	if (lower_attribute == nullptr)
		throw std::runtime_error(FUNCTION_NAME);

	if (m_attributes.find(lower_attribute->getName()) != m_attributes.end())
		throw ResourceAlradeyExists(lower_attribute->getName(), FUNCTION_NAME);

	m_attributes[lower_attribute->getName()] = std::move(lower_attribute);
}

void CompositeAttribute::getValue(const std::string& attribute_name, int& value) const
{
	std::string base_name, lower_name;
	std::map<std::string, std::unique_ptr<IAttribute>>::const_iterator it;

	splitAttributeName(attribute_name, base_name, lower_name);

	if (base_name != m_name)
		throw ResourceDoesNotExists(base_name, FUNCTION_NAME);

	it = m_attributes.find(lower_name);
	if (it == m_attributes.end())
		throw ResourceDoesNotExists(lower_name, FUNCTION_NAME);

	it->second->getValue(lower_name, value);
}

void CompositeAttribute::setValue(const std::string& attribute_name, int value)
{
	std::string base_name, lower_name;
	std::map<std::string, std::unique_ptr<IAttribute>>::const_iterator it;

	splitAttributeName(attribute_name, base_name, lower_name);

	if (base_name != m_name)
		throw ResourceDoesNotExists(base_name, FUNCTION_NAME);

	it = m_attributes.find(lower_name);
	if (it == m_attributes.end())
		throw ResourceDoesNotExists(lower_name, FUNCTION_NAME);

	it->second->setValue(lower_name, value);
}

void CompositeAttribute::splitAttributeName(const std::string& full_name, std::string& base_name, std::string& lower_name) const
{
	std::stringstream ss;

	if (full_name.find('.') == std::string::npos)
		throw StringSplittingFail(full_name);

	ss.str(full_name);
	std::getline(ss, base_name, '.');
	ss >> lower_name;

	if (base_name.size() == 0 || lower_name.size() == 0)
		throw StringSplittingFail(full_name);
}

void CompositeAttribute::dump(ILogger& l)
{
	l << "name : \"" << m_name << "\"\n";
	l.startBlock("children attributes");
	for (auto& a : m_attributes)
		a.second->dump(l);
	l.endBlock();
}