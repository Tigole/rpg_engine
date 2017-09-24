#include "BasicCharacter.hpp"

#include "Skill/ISkill.hpp"
#include "Skill/SkillManager.hpp"
#include "Logger/ILogger.h"
#include "Exception/Exception.hpp"

void deleteBasiCharacter(ICharacter* obj)
{
	delete obj;
}

BasicCharacter::BasicCharacter(const std::string& name)
	:m_attributes(),
	m_name(name),
	m_targets(),
	m_ennemies(),
    m_skills(),
    m_current_skill(nullptr)
{
	/** Nothing **/
}

/*BasicCharacter::BasicCharacter(const BasicCharacter& bc)
 : m_attributes(),
	m_name(bc.m_name),
	m_targets(),
	m_ennemies(),
	m_skills(),
	m_current_skill(nullptr)
{
	for (auto& attribute : bc.m_attributes)
		m_attributes[attribute.first] = std::move(attribute.second->clone());
	for (auto& skill : bc.m_skills)
		m_skills.push_back(std::move(skill->clone()));
}

BasicCharacter& BasicCharacter::operator=(const BasicCharacter& bc)
{
	m_attributes = bc.m_attributes;
	m_name = bc.m_name;
	m_targets.resize(0);
	m_ennemies.resize(0);
	m_skills.clear();
	m_current_skill = nullptr;

	for (auto& skill : bc.m_skills)
		m_skills.push_back(std::move(skill->clone()));

	return *this;
}*/

BasicCharacter::~BasicCharacter()
{
	/** Nothing : for smart pointer **/
}

const std::string& BasicCharacter::mt_Get_Name(void) const
{
	return m_name;
}

void BasicCharacter::mt_Get_Attribute(const std::string& attribute_id, int& attribute_value) const
{
	auto l_it(m_attributes.find(attribute_id));

	if (l_it == m_attributes.end())
		throw ExceptionAttributeNotFound(attribute_id, "BasicCharacter", mt_Get_Name());
	l_it->second->mt_Get_Value(attribute_id, attribute_value);
}

void BasicCharacter::mt_Get_Attribute(const std::string& attribute_id, int& attribute_value)
{
	auto l_it(m_attributes.find(attribute_id));

	if (l_it == m_attributes.end())
		throw ExceptionAttributeNotFound(attribute_id, "BasicCharacter", mt_Get_Name());

	l_it->second->mt_Get_Value(attribute_id, attribute_value);
}

void BasicCharacter::mt_Set_Attribute(const std::string& attribute_id, int attribute_value)
{
	auto l_it(m_attributes.find(attribute_id));

	if (l_it == m_attributes.end())
		throw ExceptionAttributeNotFound(attribute_id, "BasicCharacter", mt_Get_Name());
	l_it->second->mt_Set_Value(attribute_id, attribute_value);
}

void BasicCharacter::mt_Start_Turn(void)
{
	for (auto it = m_attributes.begin(); it != m_attributes.end(); it++)
		it->second->mt_Start_Turn();
}

void BasicCharacter::mt_End_Turn(void)
{
	for (auto it = m_attributes.begin(); it != m_attributes.end(); it++)
		it->second->mt_End_Turn();
}

void BasicCharacter::mt_Select_Skill(void)
{
	throw ExceptionUnimplementedFunction(FUNCTION_NAME);
}

void BasicCharacter::mt_Use_Skill(void)
{
	throw ExceptionUnimplementedFunction(FUNCTION_NAME);
}

bool BasicCharacter::mt_Is_Dead(void) const
{
	bool l_ret(false);

	return l_ret;
}

std::unique_ptr<ICharacter> BasicCharacter::mt_Clone(void) const
{
	BasicCharacter* other(new BasicCharacter(m_name));
	other->m_name = m_name;
	other->m_targets.resize(0);
	other->m_ennemies.resize(0);
	other->m_skills.clear();
	other->m_current_skill = nullptr;

	for (auto& attribute : m_attributes)
		other->m_attributes[attribute.first] = attribute.second->mt_Clone();

	for (auto& skill : m_skills)
		other->m_skills.push_back(std::move(skill->mt_Clone()));

	return std::unique_ptr<ICharacter>(other);
}

void BasicCharacter::mt_Set_Ennemies(const std::vector<ICharacter*>& ennemies)
{
	m_ennemies = ennemies;
}

void BasicCharacter::mt_Add_Skill(const std::string& skill_name, const SkillManager& sm)
{
	std::unique_ptr<ISkill> new_skill(nullptr);

	new_skill = sm.mt_Get_Skill(skill_name, *this);

	if (new_skill == nullptr)
	{
		log().mt_Entrance_Function(FUNCTION_NAME);
		log() << "Skill can't be find : \"" << skill_name << "\"\n";
		log().mt_Exit_Function();
	}
	else
	{
		m_skills.push_back(std::move(new_skill));
	}
}

void BasicCharacter::mt_Dump(ILogger& l)
{
	l.mt_Entrance_Function(FUNCTION_NAME);

	l << "name : " << m_name << "\n";
	l.mt_Start_Block("attributes");
	for (auto& a : m_attributes)
		a.second->mt_Dump(l);
	l.mt_End_Block();
	l.mt_Start_Block("skills");
	l << "number of skills : " << m_skills.size() << "\n";
	for (auto& skill : m_skills)
	{
		l << skill->mt_Get_Name() << "\n";
	}
	l.mt_End_Block();
	l.mt_Start_Block("fight");
	l << "number of ennemies : " << m_ennemies.size() << "\n";
	l << "number of targets : " << m_targets.size() << "\n";
	if (m_current_skill != nullptr)
		l << "Current skill : " << m_current_skill->mt_Get_Name() << "\n";
	else
		l << "No current skill\n";
	l.mt_End_Block();

	l.mt_Exit_Function();
}
