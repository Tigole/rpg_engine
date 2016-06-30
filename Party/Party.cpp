#include "Party.hpp"
#include "Character/ICharacter.hpp"

Party::Party()
	:m_members()
{
	/** Nothing **/
}

Party::~Party()
{
	/** Nothing **/
}

void Party::setEnnemies(const std::vector<IParty*>& ennemies_parties)
{
	std::vector<ICharacter*> ennemies;

	for (auto& ennemy_party : ennemies_parties)
	{
		for (auto& party_member : ennemy_party->getMembers())
		{
			ennemies.push_back(party_member);
		}
	}

	for (auto& party_member : m_members)
		party_member->setEnnemies(ennemies);
}

std::vector<ICharacter*>& Party::getMembers(void)
{
	return m_members;
}

void Party::addMember(ICharacter* new_party_member)
{
	m_members.push_back(new_party_member);
}