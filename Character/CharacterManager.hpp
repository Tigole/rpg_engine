#ifndef _CHARACTER_MANAGER_HPP
#define _CHARACTER_MANAGER_HPP 1

#include <string>
#include <map>
#include <memory>
#include <vector>

class ICharacter;
class CharacterLoader;
class TiXmlDocument;
class SkillManager;

class CharacterManager
{
public:
	CharacterManager();

	bool load(const std::string& file_path, const std::vector<CharacterLoader*>& loaders, SkillManager& sm);

	std::unique_ptr<ICharacter> getCharacter(const std::string& character_name);

private:
	bool isValid(const TiXmlDocument& document) const;

	std::map<std::string, std::unique_ptr<ICharacter>> m_characters;
};

#endif // _CHARACTER_MANAGER_HPP
