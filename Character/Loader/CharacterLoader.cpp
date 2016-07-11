#include "CharacterLoader.hpp"
#include "Logger/ILogger.h"
#include "tinyxml.h"

CharacterLoader::CharacterLoader(const std::string& element_name)
 :	Loader(element_name)
{
	/** Nothing **/
}

CharacterLoader::~CharacterLoader()
{
	/** Nothing **/
}

ICharacter* CharacterLoader::load(const TiXmlElement& element, SkillManager& sm)
{
	ICharacter*  l_ret(nullptr);

	log().entranceFunction(FUNCTION_NAME);

	if (isValid(element))
		l_ret = loadCharacter(element, sm);
	else
	{
		log().entranceFunction(FUNCTION_NAME);
		log() << "Element is not valid : \"" << element.Value() << "\"\n";
		log().exitFunction();
	}

	log().exitFunction();

	return l_ret;
}

