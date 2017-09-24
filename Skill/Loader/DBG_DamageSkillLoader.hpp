#ifndef _DBG_DAMAGESKILLLOADER_HPP
#define _DBG_DAMAGESKILLLOADER_HPP 1

#include "SkillLoader.hpp"

class DBG_DamageSkillLoader : public SkillLoader
{
public:
	DBG_DamageSkillLoader(const std::string& element_name);

	std::unique_ptr<ISkill> mt_Load(const TiXmlElement& element);
};

#endif // _DBG_DAMAGESKILLLOADER_HPP
