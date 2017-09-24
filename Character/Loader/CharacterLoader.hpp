#ifndef _CHARACTER_LOADER_HPP
#define _CHARACTER_LOADER_HPP 1

#include <string>
#include <vector>
#include "Loader/Loader.hpp"
#include "Miscellaneous.hpp"

class TiXmlElement;
class SkillManager;
class ICharacter;

class CharacterLoader : public Loader
{
public:
	CharacterLoader(const std::string& element_name);
	virtual ~CharacterLoader();

	virtual std::unique_ptr<ICharacter> mt_Load(const TiXmlElement& element, SkillManager& sm) = 0;
};

#endif // _CHARACTER_LOADER_HPP
