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

void Party::mt_Set_Ennemies(const std::vector<IParty*>& ennemies_parties)
{
	std::vector<ICharacter*> ennemies;

	for (auto& ennemy_party : ennemies_parties)
	{
		for (auto& party_member : ennemy_party->mt_Get_Members())
		{
			ennemies.push_back(party_member);
		}
	}

	for (auto& party_member : m_members)
		party_member->mt_Set_Ennemies(ennemies);
}

std::vector<ICharacter*>& Party::mt_Get_Members(void)
{
	return m_members;
}

void Party::mt_Add_Member(ICharacter* new_party_member)
{
	m_members.push_back(new_party_member);
}
