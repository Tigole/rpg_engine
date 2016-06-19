#include "Character.hpp"


Character::Character(const std::string& name, int hp)
	:BasicCharacter(name, misc::Gauge<int>(hp))
{
	/** Nothing **/
}

void Character::selectSkill(void)
{
	/** Choose skill **/
	/** Choose target for the skill **/
}

void Character::useSkill(void)
{
	//
}