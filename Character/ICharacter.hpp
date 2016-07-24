#ifndef _ICHARACTER_HPP
#define _ICHARACTER_HPP 1

#include <vector>
#include <string>

#include "Miscellaneous.hpp"

class SkillManager;

class ICharacter : public misc::Clonable<ICharacter>, public misc::Dumpable
{
public:
	virtual ~ICharacter() {}

	/** Init methods **/
	virtual void setEnnemies(const std::vector<ICharacter*>& ennemies) = 0;

	/** Fight methods **/
	virtual void selectSkill(void) = 0;
	virtual void useSkill(void) = 0;
	virtual bool getAttribute(const std::string& attribute_id, int& attribute_value) = 0;
	virtual bool setAttribute(const std::string& attribute_id, int attribute_value) = 0;

	/** States methods **/
	virtual const std::string& getName(void) = 0;
	virtual bool isDead(void) const = 0;

	/** Other **/
	virtual void addSkill(const std::string& skill_name, const SkillManager& sm) = 0;
};

#endif // !_ICHARACTER_HPP
