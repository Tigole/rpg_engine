#ifndef _PARTY_HPP
#define _PARTY_HPP 1

#include "IParty.hpp"

class Party : public IParty
{
public:
	Party();
	virtual ~Party();
	virtual void setEnnemies(const std::vector<IParty*>& ennemies);

	virtual std::vector<ICharacter*>& getMembers(void);
	virtual void addMember(ICharacter* new_party_member);

protected:
	std::vector<ICharacter*> m_members;
};

#endif // !_PARTY_HPP