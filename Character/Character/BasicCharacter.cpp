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

const std::string& BasicCharacter::getName(void) const
{
	return m_name;
}

void BasicCharacter::getAttribute(const std::string& attribute_id, int& attribute_value) const
{
	auto l_it(m_attributes.find(attribute_id));

	if (l_it == m_attributes.end())
		throw AttributeNotFound(attribute_id, "BasicCharacter", getName());
	l_it->second->getValue(attribute_id, attribute_value);
}

void BasicCharacter::getAttribute(const std::string& attribute_id, int& attribute_value)
{
	auto l_it(m_attributes.find(attribute_id));

	if (l_it == m_attributes.end())
		throw AttributeNotFound(attribute_id, "BasicCharacter", getName());

	l_it->second->getValue(attribute_id, attribute_value);
}

void BasicCharacter::setAttribute(const std::string& attribute_id, int attribute_value)
{
	auto l_it(m_attributes.find(attribute_id));

	if (l_it == m_attributes.end())
		throw AttributeNotFound(attribute_id, "BasicCharacter", getName());
	l_it->second->setValue(attribute_id, attribute_value);
}

void BasicCharacter::startTurn(void)
{
	for (auto it = m_attributes.begin(); it != m_attributes.end(); it++)
		it->second->startTurn();
}

void BasicCharacter::endTurn(void)
{
	for (auto it = m_attributes.begin(); it != m_attributes.end(); it++)
		it->second->endTurn();
}

void BasicCharacter::selectSkill(void)
{
	throw UnimplementedFunction(FUNCTION_NAME);
}

void BasicCharacter::useSkill(void)
{
	throw UnimplementedFunction(FUNCTION_NAME);
}

bool BasicCharacter::isDead(void) const
{
	bool l_ret(false);

	return l_ret;
}

std::unique_ptr<ICharacter> BasicCharacter::clone(void) const
{
	BasicCharacter* other(new BasicCharacter(m_name));
	other->m_name = m_name;
	other->m_targets.resize(0);
	other->m_ennemies.resize(0);
	other->m_skills.clear();
	other->m_current_skill = nullptr;

	for (auto& attribute : m_attributes)
		other->m_attributes[attribute.first] = attribute.second->clone();

	for (auto& skill : m_skills)
		other->m_skills.push_back(std::move(skill->clone()));

	return std::unique_ptr<ICharacter>(other);
}

void BasicCharacter::setEnnemies(const std::vector<ICharacter*>& ennemies)
{
	m_ennemies = ennemies;
}

void BasicCharacter::addSkill(const std::string& skill_name, const SkillManager& sm)
{
	std::unique_ptr<ISkill> new_skill(nullptr);

	new_skill = sm.getSkill(skill_name, *this);

	if (new_skill == nullptr)
	{
		log().entranceFunction(FUNCTION_NAME);
		log() << "Skill can't be find : \"" << skill_name << "\"\n";
		log().exitFunction();
	}
	else
	{
		m_skills.push_back(std::move(new_skill));
	}
}

void BasicCharacter::dump(ILogger& l)
{
	l.entranceFunction(FUNCTION_NAME);

	l << "name : " << m_name << "\n";
	l.startBlock("attributes");
	for (auto& a : m_attributes)
		a.second->dump(l);
	l.endBlock();
	l.startBlock("skills");
	l << "number of skills : " << m_skills.size() << "\n";
	for (auto& skill : m_skills)
	{
		l << skill->getName() << "\n";
	}
	l.endBlock();
	l.startBlock("fight");
	l << "number of ennemies : " << m_ennemies.size() << "\n";
	l << "number of targets : " << m_targets.size() << "\n";
	if (m_current_skill != nullptr)
		l << "Current skill : " << m_current_skill->getName() << "\n";
	else
		l << "No current skill\n";
	l.endBlock();

	l.exitFunction();
}
