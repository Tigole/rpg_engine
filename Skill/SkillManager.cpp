#include "SkillManager.hpp"
#include "Skill/ISkill.hpp"
#include "Logger/ILogger.h"
#include "Loader/SkillLoader.hpp"

#include "Exception/Exception.hpp"

#include <algorithm>

SkillManager::SkillManager()
 :  m_skills()
{
    /** Nothing **/
}

void SkillManager::load(const std::string& file_path, const std::map<std::string, std::unique_ptr<SkillLoader>>& loaders)
{
	TiXmlDocument l_doc;
	TiXmlAttribute* l_attribute(nullptr);
	const TiXmlElement* root(nullptr);
	std::map<std::string, std::unique_ptr<SkillLoader>>::const_iterator l_it(loaders.end());
	std::unique_ptr<ISkill> l_tmp_skill(nullptr);

	log().entranceFunction(FUNCTION_NAME);

	if (l_doc.LoadFile(file_path) == false)
		throw Exception(std::string(FUNCTION_NAME) + " : \"l_doc.LoadFile(" + file_path + ")\"");

	root = l_doc.RootElement();

	if (root->NoChildren() == true)
		throw XMLLoadingExceptionElementHasNoChild(*root);

	for (const TiXmlElement* l_element = root->FirstChildElement(); l_element != nullptr; l_element = l_element->NextSiblingElement())
	{
		l_it = loaders.find(l_element->ValueStr());

		if (l_it == loaders.end())
			throw XMLLoadingExceptionNoLoader(l_element->ValueStr());

		l_tmp_skill = (l_it->second)->load(*l_element);

		m_skills[l_tmp_skill->getName()] = std::move(l_tmp_skill);
	}
}

std::unique_ptr<ISkill> SkillManager::getSkill(const std::string& skill_name, ICharacter& skill_owner) const
{
	std::unique_ptr<ISkill> l_ret(nullptr);
	std::map<std::string, std::unique_ptr<ISkill>>::const_iterator l_it(m_skills.find(skill_name));

	if (l_it == m_skills.end())
		throw ResourceDoesNotExists(skill_name, FUNCTION_NAME);

	l_ret = std::move(l_it->second->clone());

	l_ret->setOwner(skill_owner);

	return l_ret;
}
