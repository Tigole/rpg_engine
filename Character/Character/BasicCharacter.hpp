#ifndef _BASIC_CHARACTER_HPP
#define _BASIC_CHARACTER_HPP 1

#include "Character/ICharacter.hpp"
#include "Miscellaneous.hpp"
#include <string>
#include <memory>
#include <map>

class ISkill;

class BasicCharacter : public ICharacter
{
public:
	BasicCharacter(const std::string& name, const misc::Gauge<int>& hp);
	BasicCharacter(const BasicCharacter& bc);
	BasicCharacter& operator=(const BasicCharacter& bc);
	~BasicCharacter();
	virtual const std::string& getName(void);
	virtual void setEnnemies(const std::vector<ICharacter*>& ennemies);
	virtual bool getAttribute(const std::string& attribute_id, int& attribute_value) const;
	virtual bool getAttribute(const std::string& attribute_id, int& attribute_value);
	virtual bool setAttribute(const std::string& attribute_id, int attribute_value);

	virtual void addSkill(const std::string& skill_name, const SkillManager& sm);

	virtual void dump(ILogger& l);
protected:

	/*void selectSkill(void);
	void selectTarget(void);*/

	std::map<std::string, int> m_attributes;
	std::string m_name;
	std::vector<ICharacter*> m_targets;
	std::vector<ICharacter*> m_ennemies;
	std::vector<std::unique_ptr<ISkill>> m_skills;
	ISkill* m_current_skill;
};

#endif // !_BASIC_CHARACTER_HPP
