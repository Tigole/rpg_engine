#ifndef _SKILL_LOADER_HPP
#define _SKILL_LOADER_HPP 1

#include <string>
#include "Miscellaneous.hpp"

class TiXmlElement;
class ISkill;

class SkillLoader : public misc::Loader
{
public:
	SkillLoader(const std::string& element_name);
	virtual ~SkillLoader();

	ISkill* load(const TiXmlElement& element);

protected:

	virtual bool isValid(const TiXmlElement& element) const = 0;
	virtual ISkill* loadElement(const TiXmlElement& element) = 0;
};

#endif // !_SKILL_LOADER_HPP
