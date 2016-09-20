#ifndef _DBG_CHARACTER_LOADER_HPP
#define _DBG_CHARACTER_LOADER_HPP 1

#include "CharacterLoader.hpp"

class ICharacter;
class TiXmlElement;

class DBG_CharacterLoader : public CharacterLoader
{
public:
	DBG_CharacterLoader(const std::string& element_name);

protected:
	bool isValid(const TiXmlElement& element);
	bool checkSkills(const TiXmlElement& skills);
	std::unique_ptr<ICharacter> loadCharacter(const TiXmlElement& element, SkillManager& sm);
	std::vector<std::string> loadSkills(const TiXmlElement& skills_element);
};



#endif // _DBG_CHARACTER_LOADER_HPP
