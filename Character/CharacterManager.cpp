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

void CharacterManager::mt_Load(const std::string& file_path, const std::map<std::string, std::unique_ptr<CharacterLoader>>& loaders, SkillManager& sm)
{
	TiXmlDocument document;
	std::map<std::string, std::unique_ptr<CharacterLoader>>::const_iterator l_it;
	std::unique_ptr<ICharacter> l_tmp_char(nullptr);
	const TiXmlElement* root(nullptr);

	if (document.LoadFile(file_path) == false)
		throw Exception(std::string(FUNCTION_NAME) + " : \"document.LoadFile(" + file_path + ") == false\"");

	root = document.RootElement();

	if (root->NoChildren() == true)
		throw ExceptionXMLLoadingElementHasNoChild(*root);

	for (const TiXmlElement* l_element = root->FirstChildElement(); l_element != nullptr; l_element = l_element->NextSiblingElement())
	{
		l_it = loaders.find(l_element->ValueStr());

		if (l_it == loaders.end())
			throw ExceptionXMLLoadingNoLoader(l_element->ValueStr());

		l_tmp_char = (l_it->second)->mt_Load(*l_element, sm);
		m_characters[l_tmp_char->mt_Get_Name()] = std::move(l_tmp_char);
	}
}

std::unique_ptr<ICharacter> CharacterManager::mt_Get_Character(const std::string& character_id)
{
	auto l_it(m_characters.find(character_id));

	if (l_it == m_characters.end())
		throw ExceptionResourceDoesNotExists(character_id, FUNCTION_NAME);

	return l_it->second->mt_Clone();
}
