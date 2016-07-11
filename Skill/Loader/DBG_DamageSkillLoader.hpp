#ifndef _DBG_DAMAGESKILLLOADER_HPP
#define _DBG_DAMAGESKILLLOADER_HPP 1

#include "SkillLoader.hpp"

class DBG_DamageSkillLoader : public SkillLoader
{
public:
	DBG_DamageSkillLoader(const std::string& element_name);
protected:
	bool isValid(const TiXmlElement& element) const;
	ISkill* loadElement(const TiXmlElement& element);
};

#endif // _DBG_DAMAGESKILLLOADER_HPP
