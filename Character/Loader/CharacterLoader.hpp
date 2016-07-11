#ifndef _CHARACTER_LOADER_HPP
#define _CHARACTER_LOADER_HPP 1

#include <string>
#include <vector>
#include "Miscellaneous.hpp"

class TiXmlElement;
class SkillManager;
class ICharacter;

class CharacterLoader : public misc::Loader
{
public:
	CharacterLoader(const std::string& element_name);
	virtual ~CharacterLoader();

	ICharacter* load(const TiXmlElement& element, SkillManager& sm);

protected:
	virtual bool isValid(const TiXmlElement& element) = 0;
	virtual ICharacter* loadCharacter(const TiXmlElement& element, SkillManager& sm) = 0;
};

#endif // _CHARACTER_LOADER_HPP
