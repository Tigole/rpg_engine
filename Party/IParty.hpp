#ifndef _IPARTY_HPP
#define _IPARTY_HPP 1

#include <vector>

class ICharacter;

class IParty
{
public:
	virtual ~IParty(){}

	virtual void mt_Set_Ennemies(const std::vector<IParty*>& ennemies_parties) = 0;

	virtual std::vector<ICharacter*>& mt_Get_Members(void) = 0;
	virtual void mt_Add_Member(ICharacter* new_party_member) = 0;
};

#endif // !_IPARTY_HPP
