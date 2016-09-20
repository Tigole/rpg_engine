#include "BasicCharacterLoader.hpp"
#include "Character\Character\BasicCharacter.hpp"
#include "Skill\SkillManager.hpp"

#include <tinyxml.h>

BasicCharacterLoader::BasicCharacterLoader()
	:CharacterLoader("BasicCharacter")
{
	/** Nothing **/
}

void BasicCharacterLoader::setAttributeLoaderFactory(AttributeLoaderFactory* attribute_loader_factory)
{
	m_attribute_loader_factory = attribute_loader_factory;
}


bool BasicCharacterLoader::isValid(const TiXmlElement& element)
{
	bool l_ret(true);

	return l_ret;
}

std::unique_ptr<ICharacter> BasicCharacterLoader::loadCharacter(const TiXmlElement& element, SkillManager& sm)
{
	BasicCharacter* l_ret(nullptr);
	bool b(false);
	const TiXmlElement* l_element(nullptr);
	std::vector<std::string> skill_id;
	const char* character_name(nullptr);

	character_name = element.Attribute("name");
	if (character_name != nullptr)
	{
		l_element = element.FirstChildElement("SkillList");
		if (l_element != nullptr)
		{
			b = loadSkillList(*l_element, skill_id);
		}
	}


	if (b == true)
	{
		l_ret = new BasicCharacter(character_name);
		if (l_ret != nullptr)
		{
			l_element = element.FirstChildElement("AttributeList");
			if (l_element != nullptr)
			{
				b = loadAttributList(*l_element, *l_ret);
			}
			else
			{
				log().entranceFunction(FUNCTION_NAME);
				log() << "No child \"AttributeList\"\n";
				log().exitFunction();
			}
		}
		else
		{
			log().entranceFunction(FUNCTION_NAME);
			log() << "Error while new\n";
			log().exitFunction();
		}
	}
	else
	{
		log().entranceFunction(FUNCTION_NAME);
		log() << "No child \"SkillList\"\n";
		log().exitFunction();
	}

	if (b == true)
	{
		for (auto& skill : skill_id)
			l_ret->addSkill(skill, sm);
	}

	return std::unique_ptr<ICharacter>(l_ret);
}

bool BasicCharacterLoader::loadSkillList(const TiXmlElement& element, std::vector<std::string>& skill_id)
{
	bool l_ret(true);
	const char* tmp(nullptr);

	for (const TiXmlNode* l_node = element.FirstChild(); (l_ret == true) && (l_node != nullptr); l_node = l_node->NextSibling())
	{
		const TiXmlElement* l_element(l_node->ToElement());
		if (l_element != nullptr)
		{
			l_ret = false;
			if (l_element->ValueStr() == "Skill")
			{
				tmp = l_element->Attribute("id");
				if (tmp != nullptr)
				{
					skill_id.push_back(tmp);
					l_ret = true;
				}
				else
				{
					log().entranceFunction(FUNCTION_NAME);
					log() << "No \"id\" in \"Skill\"\n";
					log().exitFunction();
				}
			}
			else
			{
				log().entranceFunction(FUNCTION_NAME);
				log() << "Unexpected element \"" << l_element->Value() << "\" in AttributeList\n";
				log().exitFunction();
			}
		}
	}

	return l_ret;
}

bool BasicCharacterLoader::loadAttributList(const TiXmlElement& element, BasicCharacter& character)
{
	bool l_ret(false);

	return l_ret;
}