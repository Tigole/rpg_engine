#include "AttributeListLoader.hpp"
#include "Attribute/Loader/AttributeLoaderFactory.hpp"
#include "AttributeLoader.hpp"
#include "Logger/ILogger.h"
#include "Exception/Exception.hpp"

#include <tinyxml.h>

AttributeListLoader::AttributeListLoader(const AttributeLoaderFactory& attribute_loader_factory)
	:Loader("AttributeList"),
	m_attribute_loader_factory(attribute_loader_factory)
{
	/** Nothing **/
}

void AttributeListLoader::load(const TiXmlElement& element, std::vector<std::unique_ptr<IAttribute>>& attributes)
{
	LoaderCreator<AttributeLoader> attribute_loader_creator;

	if (element.NoChildren() == true)
		throw ExceptionXMLLoadingElementHasNoChild(element);

	for (const TiXmlNode* l_node = element.FirstChild(); l_node != nullptr; l_node = l_node->NextSibling())
	{
		const TiXmlElement* l_element(l_node->ToElement());

		if (l_element != nullptr)
		{
			attribute_loader_creator = m_attribute_loader_factory.getLoader(l_element->Value());

			std::unique_ptr<AttributeLoader> attribute_loader(attribute_loader_creator.m_creator());

			m_attributes.second.push_back(std::move(attribute_loader->load(*l_element)));
		}
	}
}
