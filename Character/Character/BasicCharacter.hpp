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
	virtual const std::string& mt_Get_Name(void) const;
	virtual void mt_Set_Ennemies(const std::vector<ICharacter*>& ennemies);
	virtual void mt_Get_Attribute(const std::string& attribute_id, int& attribute_value) const;
	virtual void mt_Get_Attribute(const std::string& attribute_id, int& attribute_value);
	virtual void mt_Set_Attribute(const std::string& attribute_id, int attribute_value);


	virtual void mt_Start_Turn(void);
	virtual void mt_End_Turn(void);
	virtual void mt_Select_Skill(void);
	virtual void mt_Use_Skill(void);
	virtual bool mt_Is_Dead(void) const;

	std::unique_ptr<ICharacter> mt_Clone(void) const;

	virtual void mt_Add_Skill(const std::string& skill_name, const SkillManager& sm);

	virtual void mt_Dump(ILogger& l);
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
