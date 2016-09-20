#ifndef _SKILL_MANAGER_HPP
#define _SKILL_MANAGER_HPP 1

#include <string>
#include <vector>
#include <map>
#include <memory>

#include <tinyxml.h>

#include "Miscellaneous.hpp"

class ISkill;
class ICharacter;
class SkillLoader;

class SkillManager
{
public:
    SkillManager();

	bool load(const std::string& file_path, const std::vector<std::unique_ptr<SkillLoader>>& loaders);

	std::unique_ptr<ISkill> getSkill(const std::string& skill_name, ICharacter& skill_owner) const;

private:

	bool validate(const TiXmlDocument& document);

	std::map<std::string, std::unique_ptr<ISkill>> m_skills;
};

#endif // !_SKILL_MANAGER_HPP
