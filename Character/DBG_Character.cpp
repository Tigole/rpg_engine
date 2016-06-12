#include "DBG_Character.hpp"

#include <iostream>

DBG_Character::DBG_Character(const char * name, int hp_max)
	:m_hp(hp_max),
	m_name(name)
{
	std::cout << "<" << m_name << ">Hello ! My name is " << m_name << "\n";
}

DBG_Character::~DBG_Character()
{
	std::cout << "<" << m_name << "> Bye !";
}

bool DBG_Character::isDead(void) const
{
	return (m_hp <= 0);
}

void DBG_Character::selectSkill(void) const
{
	std::cout << m_name << "::selectSkill\n";
}

void DBG_Character::useSkill(ICharacter & target)
{
	std::cout << m_name << "::useSkill\n";
	target.setDamages(1);
}

int DBG_Character::setDamages(int hp_damages)
{
	std::cout << m_name << "::setDamages\n";
	std::cout << "\t" << hp_damages << " hp lost\n";
	m_hp -= hp_damages;
	std::cout << "\t" << m_hp << " hp remaining\n";
	return m_hp;
}