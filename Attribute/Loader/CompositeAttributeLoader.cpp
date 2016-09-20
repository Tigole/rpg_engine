#include "CompositeAttributeLoader.hpp"
#include "Attribute\Attribute\CompositeAttribute.hpp"
#include "BasicAttributeLoader.hpp"

#include "Logger\ILogger.h"
#include "tinyxml.h"


AttributeLoader* createCompositeAttributeLoader(void)
{
	return new CompositeAttributeLoader();
}

void deleteCompositeAttributeLoader(AttributeLoader* object)
{
	delete object;
}

CompositeAttributeLoader::CompositeAttributeLoader()
	:AttributeLoader("CompositeAttribute")
{
	/** Nothing **/
}

CompositeAttributeLoader::~CompositeAttributeLoader()
{
	/** Nothing **/
}

bool CompositeAttributeLoader::isValid(const TiXmlElement& element)
{
	bool l_ret(false);
	std::map<std::string, AttributeLoader*> validator;

	validator[m_basic_loader.getElementName()] = &m_basic_loader;
	validator[getElementName()] = this;

	l_ret = checkAttributes(element, std::vector<std::string>(1, "name"));

	if (l_ret == true)
		l_ret = !element.NoChildren();
	else
	{
		log().entranceFunction(FUNCTION_NAME);
		log() << "Element has no \"name\" attribute\n";
		log().exitFunction();
	}

	if (l_ret == true)
	{
		for (const TiXmlNode* l_node = element.FirstChild(); (l_ret == true) && (l_node != nullptr); l_node = l_node->NextSibling())
		{
			const TiXmlElement* l_element(l_node->ToElement());
			
			if (l_element != nullptr)
			{
				auto it = validator.find(l_element->Value());
				if (it != validator.end())
				{
					l_ret = it->second->isValid(*l_element);
				}
				else
				{
					log().entranceFunction(FUNCTION_NAME);
					log() << "Element \"" << l_element->Value() << "\" is not recognized\n";
					log().exitFunction();
					l_ret = false;
				}
			}
		}
	}
	else
	{
		log().entranceFunction(FUNCTION_NAME);
		log() << "Element has no children\n";
		log().exitFunction();
	}

	return l_ret;
}

std::unique_ptr<IAttribute> CompositeAttributeLoader::loadAttribute(const TiXmlElement& element)
{
	std::unique_ptr<IAttribute> l_ret(nullptr);
	CompositeAttribute* l_tmp(nullptr);
	std::string attribute_name;
	int query_return(TIXML_SUCCESS);

	if (query_return == TIXML_SUCCESS)
		query_return = element.QueryStringAttribute("name", &attribute_name);

	if (query_return == TIXML_SUCCESS)
		l_tmp = new CompositeAttribute(attribute_name);

	if (l_tmp != nullptr)
	{
		for (const TiXmlNode* l_node = element.FirstChild(); l_node != nullptr; l_node = l_node->NextSibling())
		{
			const TiXmlElement* l_element(l_node->ToElement());

			if (l_element != nullptr)
			{
				std::unique_ptr<IAttribute> l_sub_attribute(nullptr);

				if (l_element->Value() == getElementName())
					l_sub_attribute = loadAttribute(*l_element);
				else if (l_element->Value() == m_basic_loader.getElementName())
					l_sub_attribute = m_basic_loader.loadAttribute(*l_element);

				if (l_tmp != nullptr)
					l_tmp->addAttributes(l_sub_attribute);
			}
		}

		l_ret = std::unique_ptr<IAttribute>(l_tmp);
	}

	return l_ret;
}