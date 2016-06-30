#ifndef _BASIC_CHARACTER_HPP
#define _BASIC_CHARACTER_HPP 1

#include "Character/ICharacter.hpp"
#include "Miscellaneous.hpp"
#include <string>
#include <memory>

class ISkill;

class BasicCharacter : public ICharacter
{
public:
	BasicCharacter(const std::string& name, const misc::Gauge<int>& hp);
	~BasicCharacter();
	virtual bool isDead(void) const;
	virtual void setDamages(int hp_damages);
	virtual void setEnnemies(const std::vector<ICharacter*>& ennemies);
protected:

	/*void selectSkill(void);
	void selectTarget(void);*/

	misc::Gauge<int> m_hp;
	std::string m_name;
	std::vector<ICharacter*> m_targets;
	std::vector<ICharacter*> m_ennemies;
	std::vector<std::unique_ptr<ISkill>> m_skills;
	ISkill* m_current_skill;
};

#endif // !_BASIC_CHARACTER_HPP
