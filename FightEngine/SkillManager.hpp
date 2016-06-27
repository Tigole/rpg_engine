#ifndef _SKILL_MANAGER_HPP
#define _SKILL_MANAGER_HPP 1

#include <string>
#include <vector>
#include <map>
#include <memory>

#include <tinyxml.h>

class ISkill;
class ICharacter;

struct SkillManagerLoader
{
	SkillManagerLoader(const std::string& element_name);
	SkillManagerLoader(const std::string& element_name, ISkill* (*loading_function)(const TiXmlElement&));
	std::string m_element_name;
	ISkill* (*m_loading_function)(const TiXmlElement&);
};

bool operator==(const SkillManagerLoader& a, const SkillManagerLoader& b);

class SkillManager
{
public:
    SkillManager();

	bool load(const std::string& file_path, const std::vector<SkillManagerLoader>& loading_functions);

	std::unique_ptr<ISkill> getSkill(const std::string& skill_name, ICharacter& skill_owner) const;

private:

	bool validate(const TiXmlDocument& document);

	std::map<std::string, std::unique_ptr<ISkill>> m_skills;
};

#endif // !_SKILL_MANAGER_HPP
