#include "BasicSkill.hpp"

#include "FSM/FSM.hpp"


BasicSkill::BasicSkill(const sf::String& name)
	:m_owner(nullptr),
	m_name(name)
{
	//
}

BasicSkill::~BasicSkill()
{
	//
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