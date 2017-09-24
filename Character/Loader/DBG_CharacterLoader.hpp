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
	bool mt_Is_Valid(const TiXmlElement& element);
	bool mt_Check_Skills(const TiXmlElement& skills);
	std::unique_ptr<ICharacter> mt_Load(const TiXmlElement& element, SkillManager& sm);
	std::vector<std::string> mt_Load_Skills(const TiXmlElement& skills_element);
};



#endif // _DBG_CHARACTER_LOADER_HPP
