#include "DBG_DamageSkillLoader.hpp"

#include "tinyxml.h"
#include "Skill/Skill/DBG_DamageSkill.hpp"
#include "Logger/ILogger.h"
#include "Exception/Exception.hpp"


DBG_DamageSkillLoader::DBG_DamageSkillLoader(const std::string& element_name)
 :	SkillLoader(element_name)
{
	/** Nothing **/
}

std::unique_ptr<ISkill> DBG_DamageSkillLoader::mt_Load(const TiXmlElement& element)
{
	std::unique_ptr<ISkill> l_ret(nullptr);
	int l_query_return(TIXML_SUCCESS);
	std::string skill_name;
	std::string skill_operator_str;
	int skill_damages;
	DamageSkill::DamageSkillOperator skill_operator(DamageSkill::DSO_ERROR);

	if (element.QueryStringAttribute("id", &skill_name) != TIXML_SUCCESS)
		throw ExceptionXMLLoadingAttributeMissing(element, "id");

	if (element.QueryIntAttribute("damages", &skill_damages) != TIXML_SUCCESS)
		throw ExceptionXMLLoadingAttributeMissing(element, "damages");

	if (element.QueryStringAttribute("operator", &skill_operator_str) != TIXML_SUCCESS)
		throw ExceptionXMLLoadingAttributeMissing(element, "operator");

	skill_operator = DamageSkill::mt_String_To_Operator(skill_operator_str);

	l_ret.reset(new DBG_DamageSkill(skill_name, skill_damages, skill_operator));

	return l_ret;
}
