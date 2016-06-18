#ifndef _IPARTY_HPP
#define _IPARTY_HPP 1

#include <vector>

class ICharacter;

class IParty
{
public:
	virtual ~IParty(){}

	virtual void setEnnemies(const std::vector<IParty*>& ennemies_parties) = 0;

	virtual std::vector<ICharacter*>& getMembers(void) = 0;
	virtual void addMember(ICharacter* new_party_member) = 0;
};

#endif // !_IPARTY_HPP
