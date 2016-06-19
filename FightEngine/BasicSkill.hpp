#ifndef _BASIC_SKILL_HPP
#define _BASIC_SKILL_HPP 1

#include "ISkill.hpp"

#include <string>

class BasicSkill : public ISkill
{
public:
	BasicSkill(const std::string& name);
	virtual ~BasicSkill();

	virtual int use(const std::vector<ICharacter*>& targets);

protected:
	std::string m_name;
};

#endif // !_BASIC_SKILL_HPP
