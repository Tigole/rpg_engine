#include "CharacterManager.hpp"

#include "ICharacter.hpp"
#include "tinyxml.h"

#include "Logger/ILogger.h"
#include "Character/Loader/CharacterLoader.hpp"

#include <algorithm>

CharacterManager::CharacterManager()
 :	m_characters()
{
	/** Nothing **/
}

bool CharacterManager::load(const std::string& file_path, const std::vector<CharacterLoader*>& loaders, SkillManager& sm)
{
	bool l_ret(false);
	TiXmlDocument document;
	std::vector<CharacterLoader*>::const_iterator l_it;
	ICharacter* l_tmp_char(nullptr);

	l_ret = document.LoadFile(file_path);

	log().entranceFunction(FUNCTION_NAME);

	if (l_ret)
		l_ret = isValid(document);
	else
		log() << "Can't load : \"" << file_path << "\"\n";

	if (l_ret)
	{
		for (const TiXmlNode* l_node = document.FirstChild()->NextSibling()->FirstChild(); (l_ret == true) && (l_node != nullptr); l_node = l_node->NextSibling())
		{
			const TiXmlElement* l_element(l_node->ToElement());

			if (l_element != nullptr)
			{
				l_it = std::find_if(loaders.begin(), loaders.end(), [l_element](CharacterLoader* cl){ return cl->getElementName() == l_element->ValueStr(); });

				if (l_it != loaders.end())
				{
					l_tmp_char = (*l_it)->load(*l_element, sm);

					if (l_tmp_char != nullptr)
					{
						m_characters[l_tmp_char->getName()] = std::unique_ptr<ICharacter>(l_tmp_char);
					}
					else
					{
						log() << "Character loading failed : \"" << l_element->Value() << "\"\n";
						l_ret = false;
					}
				}
			}
		}
	}
	else
		log() << "File is not valid : \"" << file_path << "\"\n";

	log().exitFunction();

	return l_ret;
}

std::unique_ptr<ICharacter> CharacterManager::getCharacter(const std::string& character_name)
{
	std::unique_ptr<ICharacter> l_ret;
	auto l_it(m_characters.find(character_name));

	if (l_it != m_characters.end())
		l_ret = std::move(l_it->second->clone());

	return l_ret;
}

bool CharacterManager::isValid(const TiXmlDocument& document) const
{
	bool l_ret(true);

	return l_ret;
}
