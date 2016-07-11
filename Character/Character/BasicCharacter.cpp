#include "BasicCharacter.hpp"

#include "Skill/ISkill.hpp"
#include "Skill/SkillManager.hpp"
#include "Logger/ILogger.h"

BasicCharacter::BasicCharacter(const std::string& name, const misc::Gauge<int>& hp)
	:m_hp(hp),
	m_name(name),
	m_targets(),
	m_ennemies(),
    m_skills(),
    m_current_skill(nullptr)
{
	/** Nothing **/
}

BasicCharacter::BasicCharacter(const BasicCharacter& bc)
 :	m_hp(bc.m_hp),
	m_name(bc.m_name),
	m_targets(),
	m_ennemies(),
	m_skills(),
	m_current_skill(nullptr)
{
	for (auto& skill : bc.m_skills)
		m_skills.push_back(std::move(skill->clone()));
}

BasicCharacter::~BasicCharacter()
{
	/** Nothing : for smart pointer **/
}

const std::string& BasicCharacter::getName(void)
{
	return m_name;
}

bool BasicCharacter::isDead(void) const
{
	return m_hp.isEmpty();
}

void BasicCharacter::setDamages(int hp_damages)
{
	m_hp -= hp_damages;
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
	l << "hp : " << m_hp.m_actual_value << " / " << m_hp.m_max_value << "\n";
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
