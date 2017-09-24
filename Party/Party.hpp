#ifndef _PARTY_HPP
#define _PARTY_HPP 1

#include "IParty.hpp"

class Party : public IParty
{
public:
	Party();
	virtual ~Party();
	virtual void mt_Set_Ennemies(const std::vector<IParty*>& ennemies);

	virtual std::vector<ICharacter*>& mt_Get_Members(void);
	virtual void mt_Add_Member(ICharacter* new_party_member);

protected:
	std::vector<ICharacter*> m_members;
};

#endif // !_PARTY_HPP
