#include "SkillManager.hpp"
#include "Skill/ISkill.hpp"
#include "Logger/ILogger.h"

#include <algorithm>

SkillManagerLoader::SkillManagerLoader(const std::string& element_name)
	: m_element_name(element_name), m_loading_function(nullptr)
{
	/** Nothing **/
}

SkillManagerLoader::SkillManagerLoader(const std::string& element_name, ISkill* (*loading_function)(const TiXmlElement&))
	: m_element_name(element_name),
	m_loading_function(loading_function)
{
	/** Nothing **/
}

SkillManager::SkillManager()
 :  m_skills()
{
	log().entranceFunction(FUNCTION_NAME);
    /** Nothing **/
	log().exitFunction();
}

bool operator==(const SkillManagerLoader& a, const SkillManagerLoader &b)
{
	return a.m_element_name == b.m_element_name;
}

bool SkillManager::load(const std::string& file_path, const std::vector<SkillManagerLoader*>& loading_functions)
{
	bool l_ret(false);
	TiXmlDocument l_doc;
	TiXmlElement* l_element(nullptr);
	TiXmlAttribute* l_attribute(nullptr);
	std::vector<SkillManagerLoader*>::const_iterator l_it(loading_functions.end());
	ISkill* l_tmp_skill(nullptr);

	/** Testing functions pointer to provide segfault **/
	for (auto& lf : loading_functions)
	{
		assert(lf != nullptr);
		assert(lf->m_loading_function != nullptr);
	}

	l_ret = l_doc.LoadFile(file_path);

	if (l_ret)
		l_ret = validate(l_doc);

	if (l_ret)
	{
		for (l_element = l_doc.FirstChild()->NextSibling()->FirstChild()->ToElement(); l_element != nullptr; l_element = l_element->NextSiblingElement())
		{
			l_attribute = l_element->FirstAttribute();

			//l_it = std::find(loading_functions.begin(), loading_functions.end(), SkillManagerLoader(l_element->Value()));

			assert(l_it != loading_functions.end());

			l_tmp_skill = (*l_it)->m_loading_function(*l_element);

			if (l_tmp_skill != nullptr)
			{
				m_skills[l_attribute->ValueStr()] = std::unique_ptr<ISkill>(l_tmp_skill);
			}
		}

	}

	return l_ret;
}

std::unique_ptr<ISkill> SkillManager::getSkill(const std::string& skill_name, ICharacter& skill_owner) const
{
	std::unique_ptr<ISkill> l_ret;
	std::map<std::string, std::unique_ptr<ISkill>>::const_iterator l_it(m_skills.find(skill_name));

	assert(l_it != m_skills.end());

	l_ret.reset(l_it->second->clone());

	assert(l_ret != nullptr);

	l_ret->setOwner(skill_owner);

	return l_ret;
}

bool SkillManager::validate(const TiXmlDocument& document)
{
	bool l_ret(false);
	const TiXmlNode* l_node(document.FirstChild());
	const TiXmlElement* l_element(nullptr);
	const TiXmlAttribute* l_attribute(nullptr);

	l_node = l_node->NextSibling()->FirstChild();

	if (l_node != nullptr)
		l_ret = true;

	while ((l_ret) && (l_node != nullptr))
	{
		l_element = l_node->ToElement();
		if (l_element != nullptr)
		{
			l_ret = false;
			for (l_attribute = l_element->FirstAttribute(); l_attribute != nullptr; l_attribute = l_attribute->Next())
			{
				if (l_attribute->NameTStr() == "name")
					l_ret = true;
			}
		}
		else
		{
			l_ret = false;
		}
		l_node = l_node->NextSibling();
	}

	return l_ret;
}
