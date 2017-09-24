#ifndef _ICHARACTER_HPP
#define _ICHARACTER_HPP 1

#include <vector>
#include <string>

#include "Miscellaneous.hpp"
#include "Attribute/Characterised.hpp"
#include "Attribute/Attribute/ICharacterAttribute.hpp"

class SkillManager;

class ICharacter : public misc::Clonable<ICharacter>, public Characterised<ICharacterAttribute>
{
public:
	virtual ~ICharacter() {}

	/** Init methods **/
	virtual void mt_Set_Ennemies(const std::vector<ICharacter*>& ennemies) = 0;

	/** Fight methods **/
	virtual void mt_Start_Turn(void) = 0;
	virtual void mt_End_Turn(void) = 0;
	virtual void mt_Select_Skill(void) = 0;
	virtual void mt_Use_Skill(void) = 0;

	/** States methods **/
	virtual const std::string& mt_Get_Name(void) const = 0;
	virtual bool mt_Is_Dead(void) const = 0;

	/** Other **/
	virtual void mt_Add_Skill(const std::string& skill_id, const SkillManager& sm) = 0;
	virtual void mt_Dump(ILogger& l) = 0;
};

#endif // !_ICHARACTER_HPP
