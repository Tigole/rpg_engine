#include "BasicCharacter.hpp"


BasicCharacter::BasicCharacter(const std::string& name, const misc::Gauge<int>& hp)
	:m_hp(hp),
	m_name(name),
	m_targets(),
	m_ennemies()
{
	/** Nothing **/
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