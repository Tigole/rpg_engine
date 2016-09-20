#include "AttributeLoader.hpp"
#include "Logger\ILogger.h"
#include "Attribute\IAttribute.hpp"


AttributeLoader::AttributeLoader(const std::string& element_name)
	:Loader(element_name)
{
	/** Nothing **/
}

AttributeLoader::~AttributeLoader()
{
	/** Nothing **/
}

std::unique_ptr<IAttribute> AttributeLoader::load(const TiXmlElement& element)
{
	std::unique_ptr<IAttribute> l_ret(nullptr);

	if (isValid(element))
	{
		l_ret = loadAttribute(element);
	}
	else
	{
		log().entranceFunction(FUNCTION_NAME);
		log() << "Element is not valid: \"" << element.Value() << "\"\n";
		log().exitFunction();
	}

	return l_ret;
}