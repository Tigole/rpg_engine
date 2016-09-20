#include "BasicAttributeLoader.hpp"
#include "Attribute\Attribute\BasicAttribute.hpp"

#include "tinyxml.h"
#include "Logger\ILogger.h"


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

bool BasicAttributeLoader::isValid(const TiXmlElement& element)
{
	bool l_ret(false);
	std::vector<std::string> attributes;

	attributes.push_back("name");
	attributes.push_back("value");

	l_ret = checkAttributes(element, attributes);

	return l_ret;
}

std::unique_ptr<IAttribute> BasicAttributeLoader::loadAttribute(const TiXmlElement& element)
{
	std::unique_ptr<IAttribute> l_ret(nullptr);
	int tixml_ret(TIXML_SUCCESS);
	std::string attribute_name;
	int attribute_value;

	if (tixml_ret == TIXML_SUCCESS)
		tixml_ret = element.QueryStringAttribute("name", &attribute_name);

	if (tixml_ret == TIXML_SUCCESS)
		tixml_ret = element.QueryIntAttribute("value", &attribute_value);
	else
	{
		log().entranceFunction(FUNCTION_NAME);
		log() << "\"name\" can't be get\n";
		log().exitFunction();
	}
	
	if (tixml_ret == TIXML_SUCCESS)
		l_ret = std::unique_ptr<IAttribute>(new BasicAttribute(attribute_name, attribute_value));
	else
	{
		log().entranceFunction(FUNCTION_NAME);
		log() << "\"value\" can't be get\n";
		log().exitFunction();
	}

	return l_ret;
}