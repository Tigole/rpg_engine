#include "AttributeListLoader.hpp"
#include "Attribute\Loader\AttributeLoaderFactory.hpp"
#include "AttributeLoader.hpp"
#include "Logger\ILogger.h"

#include <tinyxml.h>

AttributeListLoader::AttributeListLoader(const AttributeLoaderFactory& attribute_loader_factory)
	:Loader("AttributeList"),
	m_attribute_loader_factory(attribute_loader_factory)
{
	/** Nothing **/
}

bool AttributeListLoader::isValid(const TiXmlElement& element)
{
	bool l_ret(false);
	AttributeLoaderFactory::LoaderCreator attribute_loader;

	if (&element != m_attributes.first)
	{
		m_attributes.second.clear();
		m_attributes.first = &element;
		l_ret = !element.NoChildren();

		if (l_ret == false)
		{
			log().entranceFunction(FUNCTION_NAME);
			log() << getElementName() << " has no child\n";
			log().exitFunction();
		}

		for (const TiXmlNode* l_node = element.FirstChild(); (l_ret == true) && (l_node != nullptr); l_node = l_node->NextSibling())
		{
			const TiXmlElement* l_element(l_node->ToElement());

			if (l_element != nullptr)
			{
				l_ret = m_attribute_loader_factory.getLoader(l_element->Value(), attribute_loader);
				if (l_ret)
				{
					std::unique_ptr<AttributeLoader> attribute_loader(attribute_loader.m_creator());

					l_ret = (attribute_loader != nullptr);
					if (l_ret == true)
					{
						std::unique_ptr<IAttribute> l_attribute(nullptr);

						l_ret = attribute_loader->isValid(*l_element);
						if (l_ret == true)
						{
							l_attribute = attribute_loader->load(*l_element);
							l_ret = (l_attribute != nullptr);
							if (l_ret == true)
							{
								m_attributes.second.push_back(std::move(l_attribute));
							}
							else
							{
								log().entranceFunction(FUNCTION_NAME);
								log() << "l_attribute == nullptr\n";
								log().exitFunction();
							}
						}
						else
						{
							log().entranceFunction(FUNCTION_NAME);
							log() << "Element \"" << l_element->Value() << "\" is not valid\n";
							log().exitFunction();
						}
					}
					else
					{
						log().entranceFunction(FUNCTION_NAME);
						log() << "attribute_loader == nullptr\n";
						log().exitFunction();
					}
				}
				else
				{
					log().entranceFunction(FUNCTION_NAME);
					log() << "Can't create AttributeLoader for \"" << l_element->Value() << "\"\n";
					log().exitFunction();
				}
			}
		}
	}
	else
	{
		l_ret = true;
	}

	if (l_ret == true)
		m_attributes.first = &element;
	else
		m_attributes.first = nullptr;

	return l_ret;
}

bool AttributeListLoader::load(const TiXmlElement& element, std::vector<std::unique_ptr<IAttribute>>& attributes)
{
	bool l_ret(true);

	if (&element != m_attributes.first)
		l_ret = isValid(element);

	if (l_ret == true)
	{
		for (auto& a : m_attributes.second)
			attributes.push_back(std::move(a->clone()));
	}
	else
	{
		log().entranceFunction(FUNCTION_NAME);
		log() << "Element \"" << element.Value() << "\"was not validated and is not valid\n";
		log().exitFunction();
	}

	return l_ret;
}
