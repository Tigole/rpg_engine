#include "CharacterLoader.hpp"
#include "Logger/ILogger.h"
#include "tinyxml.h"
#include "Character\ICharacter.hpp"

CharacterLoader::CharacterLoader(const std::string& element_name)
 :	Loader(element_name)
{
	/** Nothing **/
}

CharacterLoader::~CharacterLoader()
{
	/** Nothing **/
}

std::unique_ptr<ICharacter> CharacterLoader::load(const TiXmlElement& element, SkillManager& sm)
{
	std::unique_ptr<ICharacter> l_ret(nullptr);

	if (isValid(element))
		l_ret = loadCharacter(element, sm);
	else
	{
		log().entranceFunction(FUNCTION_NAME);
		log() << "Element is not valid : \"" << element.Value() << "\"\n";
		log().exitFunction();
	}

	return l_ret;
}

