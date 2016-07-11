#include "SkillLoader.hpp"
#include "tinyxml.h"

#include "Logger/ILogger.h"

SkillLoader::SkillLoader(const std::string& element_name)
 :	Loader(element_name)
{
	/** Nothing **/
}

SkillLoader::~SkillLoader()
{
	/** Nothing **/
}

ISkill* SkillLoader::load(const TiXmlElement& element)
{
	ISkill* l_ret(nullptr);

	log().entranceFunction(FUNCTION_NAME);

	if (isValid(element))
		l_ret = loadElement(element);
	else
		log() << "Element is not valid : \"" << element.Value() << "\"\n";

	log().exitFunction();

	return l_ret;
}