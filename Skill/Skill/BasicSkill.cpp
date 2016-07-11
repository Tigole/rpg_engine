#include "BasicSkill.hpp"

#include "FSM/FSM.hpp"


BasicSkill::BasicSkill(const std::string& name)
	:m_owner(nullptr),
	m_name(name)
{
	/** Nothing **/
}

BasicSkill::BasicSkill(const BasicSkill& bs)
 :	m_owner(nullptr),
	m_name(bs.m_name)
{
	/** Nothing **/
}

BasicSkill::~BasicSkill()
{
	/** Nothing **/
}

BasicSkill& BasicSkill::operator=(const BasicSkill& bs)
{
	m_owner = bs.m_owner;
	m_name = bs.m_name;
	return *this;
}

void BasicSkill::use(const std::vector<ICharacter*>& targets)
{
	for (auto& target : targets)
	{
		do
		{
			affectCharacter(*target);
		} while (false);
	};
}

void BasicSkill::setOwner(ICharacter& owner)
{
	m_owner = &owner;
}

const std::string& BasicSkill::getName(void) const
{
	return m_name;
}
