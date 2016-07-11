#include "SkillManager.hpp"
#include "Skill/ISkill.hpp"
#include "Logger/ILogger.h"

#include <algorithm>

#include "Loader/SkillLoader.hpp"

SkillManager::SkillManager()
 :  m_skills()
{
	log().entranceFunction(FUNCTION_NAME);
    /** Nothing **/
	log().exitFunction();
}

bool SkillManager::load(const std::string& file_path, const std::vector<SkillLoader*>& loaders)
{
	bool l_ret(false);
	TiXmlDocument l_doc;
	TiXmlElement* l_element(nullptr);
	TiXmlAttribute* l_attribute(nullptr);
	std::vector<SkillLoader*>::const_iterator l_it(loaders.end());
	ISkill* l_tmp_skill(nullptr);

	log().entranceFunction(FUNCTION_NAME);

	l_ret = l_doc.LoadFile(file_path);

	if (l_ret)
		l_ret = validate(l_doc);
	else
		log() << "Can't read file : \"" << file_path << "\"\n";

	if (l_ret)
	{
		for (l_element = l_doc.FirstChild()->NextSibling()->FirstChild()->ToElement();(l_ret) && (l_element != nullptr); l_element = l_element->NextSiblingElement())
		{
			l_it = std::find_if(loaders.begin(), loaders.end(), [l_element](SkillLoader* sl){return l_element->Value() == sl->getElementName();});
			l_attribute = l_element->FirstAttribute();

			if (l_it == loaders.end())
			{
				log() << "Can't find loader for skill : \"" << l_element->Value() << "\"\n";
				l_ret = false;
			}
			else
			{
				l_tmp_skill = (*l_it)->load(*l_element);

				if (l_tmp_skill != nullptr)
				{
					m_skills[l_attribute->ValueStr()] = std::unique_ptr<ISkill>(l_tmp_skill);
				}
				else
				{
					log() << "Skill loading failed : \"" << l_element->Value() << "\"\n";
					l_ret = false;
				}
			}
		}

		log().startBlock("Loaded skills");
		log() << "Number of skills : " << m_skills.size() << "\n";
		for (auto& skill : m_skills)
		{
			log() << "Loaded skill : \"" << skill.second->getName() << "\"\n";
		}
		log().endBlock();

	}
	else
		log() << "File is not valid : \"" << file_path << "\"\n";

	log().exitFunction();

	return l_ret;
}

std::unique_ptr<ISkill> SkillManager::getSkill(const std::string& skill_name, ICharacter& skill_owner) const
{
	std::unique_ptr<ISkill> l_ret;
	std::map<std::string, std::unique_ptr<ISkill>>::const_iterator l_it(m_skills.find(skill_name));

	assert(l_it != m_skills.end());

	l_ret = std::move(l_it->second->clone());

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
