#ifndef _SKILL_LOADER_HPP
#define _SKILL_LOADER_HPP 1

#include <string>
#include "Loader/Loader.hpp"
#include "Miscellaneous.hpp"
#include "Skill\ISkill.hpp"

class TiXmlElement;
class ISkill;

class SkillLoader : public Loader
{
public:
	SkillLoader(const std::string& element_name);
	virtual ~SkillLoader();

	virtual std::unique_ptr<ISkill> load(const TiXmlElement& element) = 0;
};

#endif // !_SKILL_LOADER_HPP
