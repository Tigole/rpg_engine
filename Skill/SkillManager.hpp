#ifndef _SKILL_MANAGER_HPP
#define _SKILL_MANAGER_HPP 1

#include <string>
#include <vector>
#include <map>
#include <memory>

#include <tinyxml.h>

#include "Miscellaneous.hpp"
#include "ISkill.hpp"
#include "Loader/SkillLoader.hpp"

class ICharacter;
class SkillLoader;

class SkillManager
{
public:
    SkillManager();

	void mt_Load(const std::string& file_path, const std::map<std::string, std::unique_ptr<SkillLoader>>& loaders);

	std::unique_ptr<ISkill> mt_Get_Skill(const std::string& skill_name, ICharacter& skill_owner) const;

private:

	std::map<std::string, std::unique_ptr<ISkill>> m_skills;
};

#endif // !_SKILL_MANAGER_HPP
