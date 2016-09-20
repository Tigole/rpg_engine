#include "Loader/Loader.hpp"
#include "Logger/ILogger.h"

#include <tinyxml.h>
#include <algorithm>

ILoader::ILoader()
{
	/** Noting **/
}

ILoader::~ILoader()
{
	/** Nothing **/
}

bool ILoader::checkAttributes(const TiXmlElement& element, const std::vector<std::string>& attributes) const
{
	bool l_ret(attributes.size() != 0);
	std::vector<std::string>::size_type i;
	const char* attrib;

	for (i = 0; (l_ret == true) && (i < attributes.size()); i++)
	{
		attrib = element.Attribute(attributes[i].c_str());
		if (attrib == nullptr)
		{
			l_ret = false;
			log().entranceFunction(FUNCTION_NAME);
			log() << "No attribute : \"" << attributes[i] << "\"\n\tIn element : \"" << element.Value() << "\"\n";
			log().exitFunction();
		}
	}
	return l_ret;
}

bool ILoader::checkChildren(const TiXmlElement& element, const std::vector<std::string>& children) const
{
	bool l_ret(true);

	for (unsigned int i = 0; (l_ret == true) && (i < children.size()); i++)
	{
		l_ret = false;
		for (const TiXmlNode* l_node = element.FirstChild(); (l_ret == false) && (l_node != nullptr); l_node = l_node->NextSibling())
		{
			const TiXmlElement* l_element(l_node->ToElement());

			if (l_element->Value() == children[i])
				l_ret = true;
		}

		if (l_ret == false)
		{
			log().entranceFunction(FUNCTION_NAME);
			log() << "Child \"" << children[i] << "\" can't be found\n";
			log().exitFunction();
		}
	}		

	return l_ret;
}

Loader::Loader(const std::string& element_name)
 :	m_element_name(element_name)
{
	/** Nothing **/
}

Loader::~Loader()
{
	/** Nothing **/
}

const std::string& Loader::getElementName(void) const
{
	return m_element_name;
}
