#ifndef _ENVIRONMENT_HPP
#define _ENVIRONMENT_HPP 1

#include "Sound/SoundSystem.hpp"
#include "Map/MapManager.hpp"
#include "Map/TilesetManager.hpp"
#include "Character/CharacterManager.hpp"
#include "Skill/SkillManager.hpp"
#include "GUI/TextureManager.hpp"
#include "ECS_Core/ECS_SystemManager.hpp"
#include "ECS_Core/ECS_EntityManager.hpp"
#include "Map/BasicMap.hpp"
#include "Map/BasicMapLoader.hpp"
#include "Events/EventManager.hpp"
#include "StringSystem/FontManager.hpp"
#include "Window/Window.hpp"
#include "GUI/GUI_Manager.hpp"
#include "StringSystem/StringManager.hpp"

#include <string>
#include <utility>
#include <vector>


using BasicMapManager = MapManager<BasicMap, BasicMapLoader>;

class Environment
{
public:
	Environment(const std::string& resource_path);

	void mt_Load(const std::string& xml_file_name);

	SoundSystem m_sound_system;
	TextureManager m_texture_manager;
	TilesetManager m_tileset_manager;
	FontManager m_font_manager;

	CharacterManager m_character_manager;
	SkillManager m_skill_manager;
	ECS_SystemManager m_system_manager;
	ECS_EntityManager m_entity_manager;


	BasicMapManager m_map_manager;
	EventManager m_event_manager;
	GUI_Manager m_gui_manager;

	StringManager m_string_manager;

	Window m_window;

private:
	std::string m_resource_path;
};

#endif // !_ENVIRONMENT_HPP
