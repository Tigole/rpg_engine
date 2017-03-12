#ifndef _CHARACTERISED_HPP
#define _CHARACTERISED_HPP 1

#include "Attribute/ICharacterised.hpp"
#include "Attribute/IAttribute.hpp"
#include "Logger/ILogger.h"
#include "Exception/Exception.hpp"

template<class AttributeType>
class Characterised : public ICharacterised<AttributeType>
{
public:
	Characterised()
	 :	m_attributes()
	{
		/** Nothing **/
	}
	virtual ~Characterised()
	{
		/** Nothing **/
	}

	AttributeType* getAttribute(const std::string& attribute_name)
	{
		auto it(m_attributes.find(attribute_name));

		if (it == m_attributes.end())
			throw ExceptionAttributeNotFound(attribute_name, "ICharacterised<AttributeType>");

		return it->second.get();
	}

	void addAttribute(std::unique_ptr<AttributeType>& attribute)
	{
		auto it(m_attributes.find(attribute->getName()));

		if (it != m_attributes.end())
			throw ExceptionAttributeAlreadyExists(attribute->getName(), "ICharacterised<AttributeType>");

		m_attributes[attribute->getName()] = std::move(attribute);
	}

protected:
	std::map<std::string, std::unique_ptr<AttributeType>> m_attributes;
};

#endif // _CHARACTERISED_HPP
