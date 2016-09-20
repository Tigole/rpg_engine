#ifndef _CHARACTERISED_HPP
#define _CHARACTERISED_HPP 1

#include "Attribute/ICharacterised.hpp"
#include "Attribute/IAttribute.hpp"
#include "Logger\ILogger.h"

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
		AttributeType* l_ret(nullptr);
		auto it(m_attributes.find(attribute_name));

		if (it != m_attributes.end())
			l_ret = it->second.get();
		else
		{
			log().entranceFunction(FUNCTION_NAME);
			log() << "No attribute named \"" << attribute_name << "\"\n";
			log().exitFunction();
		}

		return l_ret;
	}

	bool addAttribute(std::unique_ptr<AttributeType>& attribute)
	{
		bool l_ret(false);
		auto it(m_attributes.find(attribute->getName()));
		
		if (it == m_attributes.end())
		{
			m_attributes[attribute->getName()] = std::move(attribute);
			l_ret = true;
		}
		else
		{
			log().entranceFunction(FUNCTION_NAME);
			log() << "Attribute \"" << attribute->getName() << "\" already exists\n";
			log().exitFunction();
		}

		return l_ret;
	}

protected:
	std::map<std::string, std::unique_ptr<AttributeType>> m_attributes;
};

#endif // _CHARACTERISED_HPP
