#ifndef _BASIC_SKILL_HPP
#define _BASIC_SKILL_HPP 1

#include "Skill/ISkill.hpp"

#include <string>

class BasicSkill : public ISkill
{
public:
	BasicSkill(const std::string& name);
	BasicSkill(const BasicSkill& bs);
	virtual ~BasicSkill();
	BasicSkill& operator=(const BasicSkill& bs);

	virtual void use(const std::vector<ICharacter*>& targets);
	virtual void setOwner(ICharacter& owner);
	virtual const std::string& getName(void) const;

protected:

	virtual int affectCharacter(ICharacter& target) = 0;

	ICharacter* m_owner;
	std::string m_name;
};

#endif // !_BASIC_SKILL_HPP
