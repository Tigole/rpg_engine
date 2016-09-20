#include "CompositeAttribute.hpp"
#include "Logger\ILogger.h"

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
	/*for (auto it = std::next(cp.m_attributes.begin()); it != cp.m_attributes.end(); it++)
		m_attributes[it->first] = it->second->clone();*/
	for (const auto& p : cp.m_attributes)
		m_attributes[p.first] = std::move(p.second->clone());
		//m_attributes[p.first] = p.second->clone();
}

std::unique_ptr<IAttribute> CompositeAttribute::clone(void) const
{
	return std::unique_ptr<IAttribute>(new CompositeAttribute(*this));
}

bool CompositeAttribute::save(TiXmlElement& parent) const
{
	bool l_ret(false);
	TiXmlElement* l_this(nullptr);

	l_this = new TiXmlElement("CompositeAttribute");
	l_ret = (l_this != nullptr);
	if (l_ret != false)
	{
		l_this->SetAttribute("name", m_name);
		for (auto it = m_attributes.begin(); (l_ret == true) && (it != m_attributes.end()); it++)
		{
			l_ret = it->second->save(*l_this);
			if (l_ret == false)
			{
				log().entranceFunction(FUNCTION_NAME);
				log() << "Error while saving attribute \"" << it->first << "\"\n";
				log().exitFunction();
			}
		}
	}

	return l_ret;
}

bool CompositeAttribute::addAttributes(std::unique_ptr<IAttribute>& lower_attribute)
{
	bool l_ret(false);

	if (lower_attribute != nullptr)
	{
		if (m_attributes.find(lower_attribute->getName()) == m_attributes.end())
		{
			m_attributes[lower_attribute->getName()] = std::move(lower_attribute);
			l_ret = true;
		}
		else
		{
			log().entranceFunction(FUNCTION_NAME);
			log() << "Attribute \"" << lower_attribute->getName() << "\" already exists\n";
			log().exitFunction();
		}
	}
	else
	{
		log().entranceFunction(FUNCTION_NAME);
		log() << "Attribute is invalid\n";
		log().exitFunction();
	}

	return l_ret;
}

bool CompositeAttribute::getValue(const std::string& attribute_name, int& value) const
{
	bool l_ret(false);
	std::string base_name, lower_name;
	std::map<std::string, std::unique_ptr<IAttribute>>::const_iterator it;

	l_ret = splitAttributeName(attribute_name, base_name, lower_name);

	if (l_ret == true)
	{
		if (base_name == m_name)
		{
			it = m_attributes.find(lower_name);
			if (it != m_attributes.end())
			{
				it->second->getValue(lower_name, value);
				l_ret = true;
			}
			else
			{
				log().entranceFunction(FUNCTION_NAME);
				log() << "\"" << lower_name << "\" is not part of \"" << m_name << "\"\n";
				log().exitFunction();
			}
		}
		else
		{
			log().entranceFunction(FUNCTION_NAME);
			log() << "\"" << base_name << "\" is not this object (" << m_name << ")\n";
			log().exitFunction();
		}
	}
	else
	{
		log().entranceFunction(FUNCTION_NAME);
		log() << "Splitting name failed\n";
		log().exitFunction();
	}

	return l_ret;
}

bool CompositeAttribute::setValue(const std::string& attribute_name, int value)
{
	bool l_ret(false);
	std::string base_name, lower_name;
	std::map<std::string, std::unique_ptr<IAttribute>>::const_iterator it;

	l_ret = splitAttributeName(attribute_name, base_name, lower_name);

	if (l_ret == true)
	{
		if (base_name == m_name)
		{
			it = m_attributes.find(lower_name);
			if (it != m_attributes.end())
			{
				it->second->setValue(lower_name, value);
				l_ret = true;
			}
			else
			{
				log().entranceFunction(FUNCTION_NAME);
				log() << "\"" << lower_name << "\" is not part of \"" << m_name << "\"\n";
				log().exitFunction();
			}
		}
		else
		{
			log().entranceFunction(FUNCTION_NAME);
			log() << "\"" << base_name << "\" is not this object (" << m_name << ")\n";
			log().exitFunction();
		}
	}
	else
	{
		log().entranceFunction(FUNCTION_NAME);
		log() << "Splitting name failed\n";
		log().exitFunction();
	}

	return l_ret;
}

bool CompositeAttribute::splitAttributeName(const std::string& full_name, std::string& base_name, std::string& lower_name) const
{
	bool l_ret(false);

	if (full_name.find('.') != std::string::npos)
	{
		std::stringstream ss;
		ss.str(full_name);
		std::getline(ss, base_name, '.');
		ss >> lower_name;
		if (base_name.size() != 0 && lower_name.size() != 0)
			l_ret = true;
		else
		{
			log().entranceFunction(FUNCTION_NAME);
			log() << "no base name or lower name in full name \"" << full_name << "\"\n";
			log().exitFunction();
		}
	}
	else
	{
		log().entranceFunction(FUNCTION_NAME);
		log() << "\"" << full_name << "\" has no \".\"\n";
		log().exitFunction();
	}

	return l_ret;
}

void CompositeAttribute::dump(ILogger& l)
{
	l << "name : \"" << m_name << "\"\n";
	l.startBlock("children attributes");
	for (auto& a : m_attributes)
		a.second->dump(l);
	l.endBlock();
}