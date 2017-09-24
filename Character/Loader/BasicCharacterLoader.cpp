#include "BasicCharacterLoader.hpp"
#include "Character/Character/BasicCharacter.hpp"
#include "Skill/SkillManager.hpp"
#include "Exception/Exception.hpp"

#include <tinyxml.h>

BasicCharacterLoader::BasicCharacterLoader()
	:CharacterLoader("BasicCharacter")
{
	/** Nothing **/
}

void BasicCharacterLoader::mt_Set_AttributeLoaderFactory(AttributeLoaderFactory* attribute_loader_factory)
{
	m_attribute_loader_factory = attribute_loader_factory;
}

std::unique_ptr<ICharacter> BasicCharacterLoader::mt_Load(const TiXmlElement& element, SkillManager& skill_manager)
{
	BasicCharacter* l_ret(nullptr);
	bool b(false);
	const TiXmlElement* l_element(nullptr);
	std::vector<std::string> skill_ids;
	std::string character_name;

	if (element.QueryStringAttribute("name", &character_name) != TIXML_SUCCESS)
		throw ExceptionXMLLoadingAttributeMissing(element, "name");

	l_ret = new BasicCharacter(character_name);

	for (const TiXmlNode* l_node = element.FirstChild(); l_node != nullptr; l_node = l_node->NextSibling())
	{
		const TiXmlElement* l_element(l_node->ToElement());

		if (l_element != nullptr)
		{
			if (l_element->ValueStr() == "SkillList")
			{
				mt_Load_SkillList(*l_element, skill_ids);

				for (auto& skill_id : skill_ids)
					l_ret->mt_Add_Skill(skill_id, skill_manager);
			}
			else if (l_element->ValueStr() == "AttributeList")
			{
				mt_Load_AttributList(*l_element, *l_ret);
			}
		}
	}

	return std::unique_ptr<ICharacter>(l_ret);
}

void BasicCharacterLoader::mt_Load_SkillList(const TiXmlElement& element, std::vector<std::string>& skill_id)
{
	std::string tmp;

	if (element.NoChildren() == true)
		throw ExceptionXMLLoadingElementHasNoChild(element);


	for (const TiXmlNode* l_node = element.FirstChild(); l_node != nullptr; l_node = l_node->NextSibling())
	{
		const TiXmlElement* l_element(l_node->ToElement());
		if (l_element != nullptr)
		{
			if (l_element->ValueStr() == "Skill")
			{
				if (l_element->QueryStringAttribute("id", &tmp) != TIXML_SUCCESS)
					throw ExceptionXMLLoadingAttributeMissing(*l_element, "id");

				skill_id.push_back(tmp);
			}
			else
			{
				log().mt_Entrance_Function(FUNCTION_NAME);
				log() << "Unexpected element \"" << l_element->Value() << "\" in AttributeList\n";
				log().mt_Exit_Function();
			}
		}
	}
}

void BasicCharacterLoader::mt_Load_AttributList(const TiXmlElement& element, BasicCharacter& character)
{
	if (element.NoChildren() == true)
		throw ExceptionXMLLoadingElementHasNoChild(element);

	throw ExceptionUnimplementedFunction(FUNCTION_NAME);
}
