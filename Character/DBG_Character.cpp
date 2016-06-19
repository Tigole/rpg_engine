#include "DBG_Character.hpp"

#include <iostream>

DBG_Character::DBG_Character(const char * name, int hp_max)
	:BasicCharacter(name, misc::Gauge<int>(hp_max))
{
	std::cout << "<" << m_name << "> Hello ! My name is " << m_name << "\n";
}

DBG_Character::~DBG_Character()
{
	std::cout << "<" << m_name << "> Bye !\n";
}

void DBG_Character::selectSkill(void)
{
	std::cout << m_name << "::selectSkill\n";
	m_targets.push_back(m_ennemies.front());
}

void DBG_Character::useSkill(void)
{
	std::cout << m_name << "::useSkill\n";

	if (!isDead())
	{
		for (auto& target : m_targets)
		{
			if (!target->isDead())
			{
				target->setDamages(1);
			}
		}
	}
}

void DBG_Character::setDamages(int hp_damages)
{
	std::cout << m_name << "::setDamages\n";
	std::cout << "\t" << hp_damages << " hp lost\n";
	m_hp -= hp_damages;
	std::cout << "\t" << m_hp.m_actual_value << " hp remaining\n";
}

