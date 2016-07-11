#include "DBG_DamageSkillLoader.hpp"

#include "tinyxml.h"
#include "Skill/Skill/DBG_DamageSkill.hpp"
#include "Logger/ILogger.h"


DBG_DamageSkillLoader::DBG_DamageSkillLoader(const std::string& element_name)
 :	SkillLoader(element_name)
{
	/** Nothing **/
}

bool DBG_DamageSkillLoader::isValid(const TiXmlElement& element) const
{
	bool l_ret(true);
	const char* attrib(nullptr);
	std::vector<std::string> attributes;

	attributes.push_back("name");
	attributes.push_back("damages");
	attributes.push_back("operator");

	for (auto& a : attributes)
	{
		attrib = element.Attribute(a.c_str());
		if (attrib == nullptr)
		{
			l_ret = false;
			log() << "no attribute : \"" << a << "\"\n";
		}
	}

	return l_ret;
}

ISkill* DBG_DamageSkillLoader::loadElement(const TiXmlElement& element)
{
	DBG_DamageSkill* l_ret(nullptr);
	int l_query_return(TIXML_SUCCESS);
	std::string skill_name;
	std::string skill_operator_str;
	int skill_damages;
	DamageSkill::DamageSkillOperator skill_operator(DamageSkill::DSO_ERROR);

	log().entranceFunction(FUNCTION_NAME);

	if (l_query_return == TIXML_SUCCESS)
		l_query_return = element.QueryStringAttribute("name", &skill_name);

	if (l_query_return == TIXML_SUCCESS)
		l_query_return = element.QueryIntAttribute("damages", &skill_damages);
	else
		log() << "no \"name\"\n";

	if (l_query_return == TIXML_SUCCESS)
		l_query_return = element.QueryStringAttribute("operator", &skill_operator_str);
	else
		log() << "no \"damages\"\n";

	if (l_query_return == TIXML_SUCCESS)
		skill_operator = DamageSkill::stringToOperator(skill_operator_str);
	else
		log() << "no \"operator\"\n";

	if (skill_operator != DamageSkill::DSO_ERROR)
		l_ret = new DBG_DamageSkill(skill_name, skill_damages, skill_operator);
	else
		log() << "operator not found : \"" << skill_operator_str << "\"\n";

	log().exitFunction();

	return l_ret;
}
