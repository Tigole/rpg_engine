#ifndef _BASIC_CHARACTER_HPP
#define _BASIC_CHARACTER_HPP 1

#include "Character/ICharacter.hpp"
#include "Miscellaneous.hpp"
#include <string>
#include <memory>
#include <map>

class ISkill;

extern "C"
{
	void deleteBasiCharacter(ICharacter* obj);
}

class BasicCharacter : public ICharacter
{
public:
	BasicCharacter(const std::string& name);
	BasicCharacter(const BasicCharacter& bc) = delete;
	BasicCharacter& operator=(const BasicCharacter& bc) = delete;
	~BasicCharacter();
	virtual const std::string& getName(void);
	virtual void setEnnemies(const std::vector<ICharacter*>& ennemies);
	virtual bool getAttribute(const std::string& attribute_id, int& attribute_value) const;
	virtual bool getAttribute(const std::string& attribute_id, int& attribute_value);
	virtual bool setAttribute(const std::string& attribute_id, int attribute_value);


	virtual void startTurn(void);
	virtual void endTurn(void);
	virtual void selectSkill(void);
	virtual void useSkill(void);
	virtual bool isDead(void) const;

	std::unique_ptr<ICharacter> clone(void) const;

	virtual void addSkill(const std::string& skill_name, const SkillManager& sm);

	virtual void dump(ILogger& l);
protected:

	/*void selectSkill(void);
	void selectTarget(void);*/

	//std::map<std::string, int> m_attributes;
	std::string m_name;
	std::vector<ICharacter*> m_targets;
	std::vector<ICharacter*> m_ennemies;
	std::vector<std::unique_ptr<ISkill>> m_skills;
	//std::vector<std::unique_ptr<IAttribute>> m_attributes;
	std::map<std::string, std::unique_ptr<ICharacterAttribute>> m_attributes;
	ISkill* m_current_skill;
};

#endif // !_BASIC_CHARACTER_HPP
