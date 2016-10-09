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
