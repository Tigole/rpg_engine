#ifndef _BASIC_SKILL_HPP
#define _BASIC_SKILL_HPP 1

#include "Skill/ISkill.hpp"

#include <SFML\System\String.hpp>

class BasicSkill : public ISkill
{
public:
	BasicSkill(const sf::String& name);
	virtual ~BasicSkill();

	virtual void use(const std::vector<ICharacter*>& targets);
	virtual void setOwner(ICharacter& owner);

protected:

	virtual int affectCharacter(ICharacter& target) = 0;

	ICharacter* m_owner;
	sf::String m_name;
};

#endif // !_BASIC_SKILL_HPP
