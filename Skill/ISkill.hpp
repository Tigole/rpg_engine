#ifndef _ISKILL_HPP
#define _ISKILL_HPP 1

#include <vector>
#include "Miscellaneous.hpp"
#include "Attribute/Characterised.hpp"
#include "Attribute/IAttribute.hpp"

class ICharacter;
class IBattleGroundWrapper;

class ISkill : public misc::Clonable<ISkill>, public Characterised<IAttribute>
{
public:
	virtual ~ISkill(){}

	virtual void mt_Use(const std::vector<IBattleGroundWrapper*>& targets) = 0;
	virtual void mt_Set_Owner(ICharacter& owner) = 0;
	virtual const std::string& mt_Get_Name(void) const = 0;
};

#endif // !_ISKILL_HPP
