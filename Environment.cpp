#include "Environment.hpp"
#include "Exception/Exception.hpp"
#include "Miscellaneous.hpp"
#include <tinyxml.h>

#include "ECS_Game/SystemRenderer.hpp"
#include "ECS_Game/SystemMovement.hpp"
#include "ECS_Game/SystemControl.hpp"
#include "ECS_Game/SystemState.hpp"
#include "ECS_Game/SystemSkeleton.hpp"

Environment::Environment(const std::string& resource_path)
	:m_sound_system(resource_path),
	m_tileset_manager(resource_path, &m_texture_manager),
	m_resource_path(resource_path),
	m_texture_manager(resource_path),
	m_font_manager(resource_path),
	m_system_manager(),
	m_entity_manager(resource_path, m_system_manager, &m_texture_manager),
	m_map_manager(resource_path, &m_tileset_manager, &m_entity_manager),
	m_gui_manager(resource_path, &m_event_manager, this, &m_particle_system),
	m_string_manager(resource_path),
	m_window(&m_event_manager, &m_gui_manager),
	m_particle_system(resource_path, &m_texture_manager)
{}

void Environment::mt_Load(const std::string& xml_file_name)
{
	TiXmlDocument l_doc;
	TiXmlHandle l_handle(&l_doc);
	std::vector<std::pair<std::string, std::string>> l_data;
	std::vector<std::pair<std::string, std::string>>::iterator l_it;
	std::string l_input_file(m_resource_path + "Data/" + xml_file_name);
	std::string l_path;
	std::map<std::string, std::unique_ptr<SkillLoader>> l_skill_loaders;
	std::map<std::string, std::unique_ptr<CharacterLoader>> l_character_loaders;

	std::vector<IResourceManager*> l_managers;

	l_managers.push_back(&m_map_manager);

	if (l_doc.LoadFile(l_input_file) == false)
		throw ExceptionResourceDoesNotExists(l_input_file, FUNCTION_NAME);

	/** Independants **/
	l_data.push_back(std::make_pair("Styles", ""));
	l_data.push_back(std::make_pair("Events", ""));
	l_data.push_back(std::make_pair("Musics", ""));
	l_data.push_back(std::make_pair("Sounds", ""));
	l_data.push_back(std::make_pair("Animation", ""));
	l_data.push_back(std::make_pair("Skills", ""));
	l_data.push_back(std::make_pair("Textures", ""));
	l_data.push_back(std::make_pair("Tilesets", ""));
	l_data.push_back(std::make_pair("Fonts", ""));
	l_data.push_back(std::make_pair("Strings", ""));
	l_data.push_back(std::make_pair("Interfaces", ""));
	/** Dependant **/
	l_data.push_back(std::make_pair("Maps", ""));
	l_data.push_back(std::make_pair("Entities", ""));
	l_data.push_back(std::make_pair("Particles", ""));
	//l_data.push_back(std::make_pair("Characters", ""));

	{
		m_system_manager.mt_Add_System<SystemState>(ECS_SystemId::STATE);
		m_system_manager.mt_Add_System<SystemControl>(ECS_SystemId::CONTROL);
		m_system_manager.mt_Add_System<SystemMovement>(ECS_SystemId::MOVEMENT);
		// Collision
		m_system_manager.mt_Add_System<SystemSkeleton>(ECS_SystemId::SKELETON);
		// Sound
		m_system_manager.mt_Add_System<SystemRenderer>(ECS_SystemId::RENDERER);
		m_system_manager.mt_Set_EntityManager(&m_entity_manager);
	}

	for (const TiXmlElement* l_child = l_handle.FirstChildElement("Data").FirstChildElement().Element(); l_child != nullptr; l_child = l_child->NextSiblingElement())
	{
		l_it = l_data.end();
		for (auto a = l_data.begin(); a != l_data.end(); a++)
			if (a->first == l_child->Value())
				l_it = a;
		if (l_it != l_data.end())
			l_child->QueryStringAttribute("path", &l_it->second);
	}

	for (const auto& a : l_data)
	{
		if (a.first == "Musics")
			m_sound_system.mt_Music_Load_Resource_Paths(m_resource_path + "Data/" + a.second);
		else if (a.first == "Sounds")
			m_sound_system.mt_Sound_Load_Resource_Paths(m_resource_path + "Data/" + a.second);
		else if (a.first == "Tilesets")
			m_tileset_manager.mt_Load_Resource_Paths(m_resource_path + "Data/" + a.second);
		else if (a.first == "Maps")
			m_map_manager.mt_Load_Resource_Paths(m_resource_path + "Data/" + a.second);
		/*else if (a.first == "Characters")
			m_character_manager.mt_Load(m_resource_path + "Data/" + a.second, l_character_loaders, m_skill_manager);*/
			/*else if (a.first == "Skills")
				m_skill_manager.mt_Load(m_resource_path + "Data/" + a.second, l_skill_loaders);*/
		else if (a.first == "Textures")
			m_texture_manager.mt_Load_Resource_Paths(m_resource_path + "Data/" + a.second);
		else if (a.first == "Fonts")
			m_font_manager.mt_Load_Resource_Paths(m_resource_path + "Data/" + a.second);
		else if (a.first == "Events")
			m_event_manager.mt_Load(m_resource_path + "Data/" + a.second);
		else if (a.first == "Interfaces")
			m_gui_manager.mt_Load_Interfaces(m_resource_path + "Data/" + a.second);
		else if (a.first == "Styles")
			m_gui_manager.mt_Load_Styles(m_resource_path + "Data/" + a.second);
		else if (a.first == "Strings")
			m_string_manager.mt_Load(m_resource_path + "Data/" + a.second);
		else if (a.first == "Entities")
			m_entity_manager.mt_Load_Paths(m_resource_path + "Data/" + a.second);
		else if (a.first == "Particles")
			m_particle_system.mt_Load(m_resource_path + "Data/" + a.second);
	}
}
