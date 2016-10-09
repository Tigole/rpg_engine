#include "BasicAttributeLoader.hpp"
#include "Attribute\Attribute\BasicAttribute.hpp"

#include "tinyxml.h"
#include "Logger\ILogger.h"

#include "Exception\Exception.hpp"

AttributeLoader* createBasicAttributeLoader(void)
{
	return new BasicAttributeLoader();
}

void deleteBasicAttributeLoader(AttributeLoader* object)
{
	delete object;
}

BasicAttributeLoader::BasicAttributeLoader()
	:AttributeLoader("BasicAttribute")
{
	/** Nothing **/
}

BasicAttributeLoader::~BasicAttributeLoader()
{
	/** Nothing **/
}

std::unique_ptr<IAttribute> BasicAttributeLoader::load(const TiXmlElement& element)
{
	std::unique_ptr<IAttribute> l_ret(nullptr);
	int tixml_ret(TIXML_SUCCESS);
	std::string attribute_name;
	int attribute_value;

	if (element.QueryStringAttribute("id", &attribute_name) != TIXML_SUCCESS)
		throw XMLLoadingExceptionAttributeMissing(element, "id");

	if (element.QueryIntAttribute("value", &attribute_value) != TIXML_SUCCESS)
		throw XMLLoadingExceptionAttributeMissing(element, "value");

	l_ret = std::unique_ptr<IAttribute>(new BasicAttribute(attribute_name, attribute_value));

	return l_ret;
}