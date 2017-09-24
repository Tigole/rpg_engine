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

bool DBG_CharacterLoader::mt_Is_Valid(const TiXmlElement& element)
{
	bool l_ret(true);
	std::vector<std::string> attributes;
	std::map<std::string, bool (DBG_CharacterLoader::*)(const TiXmlElement&)> checkers;

	checkers["Skills"] = &DBG_CharacterLoader::mt_Check_Skills;

	attributes.push_back("name");
	attributes.push_back("hp");

	l_ret = mt_Check_Attributes(element, attributes);

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
					log().mt_Entrance_Function(FUNCTION_NAME);
					log() << "Sub element is not valid : \"" << l_sub_element->Value() << "\"\n";
					log().mt_Exit_Function();
				}
			}
			else
			{
				log().mt_Entrance_Function(FUNCTION_NAME);
				log() << "No checker found for \"" << l_sub_element->Value() << "\"\n";
				log().mt_Exit_Function();
			}
		}
	}

	return l_ret;
}

bool DBG_CharacterLoader::mt_Check_Skills(const TiXmlElement& skills)
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
				l_b_ret = mt_Check_Attributes(*l_sub_element, attribs);
				if (!l_b_ret)
				{
					log().mt_Entrance_Function(FUNCTION_NAME);
					log() << "Element is not valid : \"" << l_sub_element->Value() << "\"\n";
					log().mt_Exit_Function();
				}
			}
			else
			{
				log().mt_Entrance_Function(FUNCTION_NAME);
				log() << "Element shouldn't be there : \"" << l_sub_element->Value() << "\"\n";
				log().mt_Exit_Function();
				l_b_ret = false;
			}
		}
	}

	return l_b_ret;
}

std::unique_ptr<ICharacter> DBG_CharacterLoader::mt_Load(const TiXmlElement& element, SkillManager& sm)
{
	std::unique_ptr<ICharacter> l_ret(nullptr);
	std::string character_name;
	int character_hp;
	std::vector<std::string> character_skills;
	std::string skill_name;
	std::unique_ptr<ISkill> character_skill(nullptr);

	element.QueryStringAttribute("name", &character_name);

	element.QueryIntAttribute("hp", &character_hp);

	for (auto l_sub_node = element.FirstChild(); l_sub_node != nullptr; l_sub_node = l_sub_node->NextSibling())
	{
		const TiXmlElement* l_sub_element(l_sub_node->ToElement());

		if (l_sub_element != nullptr)
		{
			if (l_sub_element->ValueStr() == "Skills")
				character_skills = mt_Load_Skills(*l_sub_element);
		}
	}

	l_ret = std::unique_ptr<ICharacter>(new DBG_Character(character_name, character_hp));

	if (l_ret != nullptr)
	{
		for (auto& skill : character_skills)
			l_ret->mt_Add_Skill(skill, sm);
	}

	return l_ret;
}

std::vector<std::string> DBG_CharacterLoader::mt_Load_Skills(const TiXmlElement& skills_element)
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
