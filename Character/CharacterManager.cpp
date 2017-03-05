#include "CharacterManager.hpp"

#include "ICharacter.hpp"
#include "tinyxml.h"

#include "Logger/ILogger.h"
#include "Character/Loader/CharacterLoader.hpp"

#include "Exception/Exception.hpp"

#include <algorithm>

CharacterManager::CharacterManager()
 :	m_characters()
{
	/** Nothing **/
}

void CharacterManager::load(const std::string& file_path, const std::map<std::string, std::unique_ptr<CharacterLoader>>& loaders, SkillManager& sm)
{
	TiXmlDocument document;
	std::map<std::string, std::unique_ptr<CharacterLoader>>::const_iterator l_it;
	std::unique_ptr<ICharacter> l_tmp_char(nullptr);
	const TiXmlElement* root(nullptr);

	if (document.LoadFile(file_path) == false)
		throw Exception(std::string(FUNCTION_NAME) + " : \"document.LoadFile(" + file_path + ") == false\"");

	root = document.RootElement();

	if (root->NoChildren() == true)
		throw XMLLoadingExceptionElementHasNoChild(*root);

	for (const TiXmlElement* l_element = root->FirstChildElement(); l_element != nullptr; l_element = l_element->NextSiblingElement())
	{
		l_it = loaders.find(l_element->ValueStr());

		if (l_it == loaders.end())
			throw XMLLoadingExceptionNoLoader(l_element->ValueStr());

		l_tmp_char = (l_it->second)->load(*l_element, sm);
		m_characters[l_tmp_char->getName()] = std::move(l_tmp_char);
	}
}

std::unique_ptr<ICharacter> CharacterManager::getCharacter(const std::string& character_name)
{
	auto l_it(m_characters.find(character_name));

	if (l_it == m_characters.end())
		throw ResourceDoesNotExists(character_name, FUNCTION_NAME);

	return l_it->second->clone();
}
