#ifndef _DAMAGE_SKILL_LOADER_HPP
#define _DAMAGE_SKILL_LOADER_HPP 1

#include "SkillLoader.hpp"

class ISkill;

class DamageSkillLoader : public SkillLoader
{
public:
	DamageSkillLoader(const std::string& element_name);

protected:
	bool isValid(const TiXmlElement& element) const;
	ISkill* loadElement(const TiXmlElement& element);
};

#endif // !_DAMAGE_SKILL_LOADER_HPP
