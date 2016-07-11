#include "DBG_CharacterLoader.hpp"

#include <map>
#include <memory>
#include <vector>
#include "tinyxml.h"
#include "Logger/ILogger.h"
#include "Character/Character/DBG_Character.hpp"
#include "Skill/ISkill.hpp"

DBG_CharacterLoader::DBG_CharacterLoader(const std::string& element_name)
 :	CharacterLoader(element_name)
{
	/** Nothing **/
}

bool DBG_CharacterLoader::isValid(const TiXmlElement& element)
{
	bool l_ret(true);
	std::vector<std::string> attributes;
	std::map<std::string, bool (DBG_CharacterLoader::*)(const TiXmlElement&)> checkers;

	checkers["Skills"] = &DBG_CharacterLoader::checkSkills;

	attributes.push_back("name");
	attributes.push_back("hp");

	l_ret = checkAttributes(element, attributes);

	for (auto l_sub_node = element.FirstChild(); (l_ret) && (l_sub_node != nullptr); l_sub_node = l_sub_node->NextSibling())
	{
		const TiXmlElement* l_sub_element(l_sub_node->ToElement());

		if (l_sub_element != nullptr)
		{
			auto l_it(checkers.find(l_sub_element->Value()));

			if (l_it != checkers.end())
			{
				l_ret = (this->*l_it->second)(*l_sub_element);
				if (!l_ret)
				{
					log().entranceFunction(FUNCTION_NAME);
					log() << "Sub element is not valid : \"" << l_sub_element->Value() << "\"\n";
					log().exitFunction();
				}
			}
			else
			{
				log().entranceFunction(FUNCTION_NAME);
				log() << "No checker found for \"" << l_sub_element->Value() << "\"\n";
				log().exitFunction();
			}
		}
	}

	return l_ret;
}

bool DBG_CharacterLoader::checkSkills(const TiXmlElement& skills)
{
	bool l_b_ret(true);
	std::vector<std::string> attribs;

	attribs.push_back("name");

	for (auto l_sub_node = skills.FirstChild(); (l_b_ret) && (l_sub_node != nullptr); l_sub_node = l_sub_node->NextSibling())
	{
		const TiXmlElement* l_sub_element(l_sub_node->ToElement());

		if (l_sub_element != nullptr)
		{
            if (l_sub_element->ValueStr() == "Skill")
			{
				l_b_ret = checkAttributes(*l_sub_element, attribs);
				if (!l_b_ret)
				{
					log().entranceFunction(FUNCTION_NAME);
					log() << "Element is not valid : \"" << l_sub_element->Value() << "\"\n";
					log().exitFunction();
				}
			}
			else
			{
				log().entranceFunction(FUNCTION_NAME);
				log() << "Element shouldn't be there : \"" << l_sub_element->Value() << "\"\n";
				log().exitFunction();
				l_b_ret = false;
			}
		}
	}

	return l_b_ret;
}

ICharacter* DBG_CharacterLoader::loadCharacter(const TiXmlElement& element, SkillManager& sm)
{
	DBG_Character* l_ret(nullptr);
	std::string character_name;
	int character_hp;
	std::vector<std::string> character_skills;
	std::string skill_name;
	std::unique_ptr<ISkill> character_skill;

	element.QueryStringAttribute("name", &character_name);

	element.QueryIntAttribute("hp", &character_hp);

	for (auto l_sub_node = element.FirstChild(); l_sub_node != nullptr; l_sub_node = l_sub_node->NextSibling())
	{
		const TiXmlElement* l_sub_element(l_sub_node->ToElement());

		if (l_sub_element != nullptr)
		{
			if (l_sub_element->ValueStr() == "Skills")
				character_skills = loadSkills(*l_sub_element);
		}
	}

	l_ret = new DBG_Character(character_name, character_hp);

	if (l_ret != nullptr)
	{
		for (auto& skill : character_skills)
			l_ret->addSkill(skill, sm);
	}

	return l_ret;
}

std::vector<std::string> DBG_CharacterLoader::loadSkills(const TiXmlElement& skills_element)
{
	std::vector<std::string> skills_names;

	for (auto l_sub_node = skills_element.FirstChild(); l_sub_node != nullptr; l_sub_node = l_sub_node->NextSibling())
	{
		std::string l_skill_name;
		const TiXmlElement* l_skill_element(l_sub_node->ToElement());

		if (l_skill_element != nullptr)
		{
			if (l_skill_element->ValueStr() == "Skill")
			{
				l_skill_element->QueryStringAttribute("name", &l_skill_name);
				skills_names.push_back(l_skill_name);
			}
		}
	}

	return skills_names;
}
