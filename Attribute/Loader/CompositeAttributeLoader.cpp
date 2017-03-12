#include "CompositeAttributeLoader.hpp"
#include "Attribute/Attribute/CompositeAttribute.hpp"
#include "BasicAttributeLoader.hpp"

#include "Logger/ILogger.h"
#include "tinyxml.h"

#include "Exception/Exception.hpp"


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

std::unique_ptr<IAttribute> CompositeAttributeLoader::load(const TiXmlElement& element)
{
	std::unique_ptr<IAttribute> l_ret(nullptr);
	CompositeAttribute* l_tmp(nullptr);
	std::string attribute_name;

	if (element.QueryStringAttribute("name", &attribute_name) != TIXML_SUCCESS)
		throw ExceptionXMLLoadingAttributeMissing(element, "name");
	if (element.NoChildren() == true)
		throw ExceptionXMLLoadingElementHasNoChild(element);

	l_tmp = new CompositeAttribute(attribute_name);

	for (const TiXmlNode* l_node = element.FirstChild(); l_node != nullptr; l_node = l_node->NextSibling())
	{
		const TiXmlElement* l_element(l_node->ToElement());

		if (l_element != nullptr)
		{
			std::unique_ptr<IAttribute> l_sub_attribute(nullptr);

			if (l_element->Value() == getElementName())
				l_sub_attribute = load(*l_element);
			else if (l_element->Value() == m_basic_loader.getElementName())
				l_sub_attribute = m_basic_loader.load(*l_element);

			l_tmp->addAttributes(l_sub_attribute);
		}
	}

	l_ret = std::unique_ptr<IAttribute>(l_tmp);

	return l_ret;
}
