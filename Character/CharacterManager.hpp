#ifndef _CHARACTER_MANAGER_HPP
#define _CHARACTER_MANAGER_HPP 1

#include <string>
#include <map>
#include <vector>
#include "Miscellaneous.hpp"
#include "ICharacter.hpp"
#include "Loader/CharacterLoader.hpp"

class TiXmlDocument;
class SkillManager;

class CharacterManager
{
public:
	CharacterManager();

	void mt_Load(const std::string& file_path, const std::map<std::string, std::unique_ptr<CharacterLoader>>& loaders, SkillManager& sm);

	std::unique_ptr<ICharacter> mt_Get_Character(const std::string& character_id);

private:

	std::map<std::string, std::unique_ptr<ICharacter>> m_characters;
};

#endif // _CHARACTER_MANAGER_HPP
