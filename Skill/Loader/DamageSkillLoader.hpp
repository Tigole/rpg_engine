#ifndef _DAMAGE_SKILL_LOADER_HPP
#define _DAMAGE_SKILL_LOADER_HPP 1

#include "SkillLoader.hpp"

class ISkill;

class DamageSkillLoader : public SkillLoader
{
public:
	DamageSkillLoader(const std::string& element_name);

protected:
	bool mt_Is_Valid(const TiXmlElement& element) const;
	std::unique_ptr<ISkill> mt_Load_Element(const TiXmlElement& element);
};

#endif // !_DAMAGE_SKILL_LOADER_HPP
