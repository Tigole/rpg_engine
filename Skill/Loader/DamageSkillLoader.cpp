#include "DamageSkillLoader.hpp"

#include "Skill/Skill/DamageSkill.hpp"
#include "tinyxml.h"

DamageSkillLoader::DamageSkillLoader(const std::string& element_name)
 :	SkillLoader(element_name)
{
	/** Nothing **/
}

bool DamageSkillLoader::isValid(const TiXmlElement& element) const
{
	bool l_ret(false);

	return l_ret;
}

ISkill* DamageSkillLoader::loadElement(const TiXmlElement& element)
{
	DamageSkill* l_ret(nullptr);
	std::string l_skill_name, l_tmp;
	int l_skill_damages;
	DamageSkill::DamageSkillOperator l_skill_operator;

	/** name **/
	element.QueryStringAttribute("name", &l_skill_name);

	/** damages **/
	element.QueryIntAttribute("damages", &l_skill_damages);

	/** operator **/
	element.QueryStringAttribute("operator", &l_tmp);
	l_skill_operator = DamageSkill::stringToOperator(l_tmp);

	/** new object **/
	//if (l_fn_returned == TIXML_SUCCESS) l_ret = new DamageSkill(l_skill_name, l_skill_damages, l_skill_operator);

	return l_ret;



	return l_ret;
}
