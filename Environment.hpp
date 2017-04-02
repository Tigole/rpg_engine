#ifndef _ENVIRONMENT_HPP
#define _ENVIRONMENT_HPP 1

#include "Sound/Music/MusicManager.hpp"
#include "Map/MapManager.hpp"
#include "Map/TilesetManager.hpp"
#include "Character/CharacterManager.hpp"
#include "Skill/SkillManager.hpp"
#include "GUI/TextureManager.hpp"

#include <string>
#include <utility>
#include <vector>

class Environment
{
public:
	Environment(const std::string& resource_path);

	void load();

	MusicManager m_music_manager;
	TilesetManager m_tileset_manager;
	MapManager m_map_manager;
	CharacterManager m_character_manager;
	SkillManager m_skill_manager;
	TextureManager m_texture_manager;

private:
	std::string m_resource_path;
};

#endif // !_ENVIRONMENT_HPP