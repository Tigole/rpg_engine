#include "Environment.hpp"
#include "Exception/Exception.hpp"
#include "Miscellaneous.hpp"
#include <tinyxml.h>

Environment::Environment(const std::string& resource_path)
	:m_music_manager(resource_path),
	m_tileset_manager(resource_path),
	m_resource_path(resource_path),
	m_texture_manager(resource_path),
	m_system_manager(),
	m_entity_manager(m_system_manager)
{}

void Environment::mt_Load()
{
	TiXmlDocument l_doc;
	TiXmlHandle l_handle(&l_doc);
	std::vector<std::pair<std::string, std::string>> l_data;
	std::vector<std::pair<std::string, std::string>>::iterator l_it;
	std::string l_input_file(m_resource_path + "Data/Environment.xml");
	std::string l_path;
	std::map<std::string, std::unique_ptr<IMapLoader>> l_map_loaders;
	std::map<std::string, std::unique_ptr<SkillLoader>> l_skill_loaders;
	std::map<std::string, std::unique_ptr<CharacterLoader>> l_character_loaders;

	if (l_doc.LoadFile(l_input_file) == false)
		throw ExceptionResourceDoesNotExists(l_input_file, FUNCTION_NAME);

	/** Independants **/
	l_data.push_back(std::make_pair("Musics", ""));
	l_data.push_back(std::make_pair("Animation", ""));
	l_data.push_back(std::make_pair("Skills", ""));
	l_data.push_back(std::make_pair("Textures", ""));
	l_data.push_back(std::make_pair("Tilesets", ""));
	/** Dependant **/
	l_data.push_back(std::make_pair("Maps", ""));
	l_data.push_back(std::make_pair("Characters", ""));

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
			m_music_manager.mt_Load(m_resource_path + "Data/" + a.second);
		else if (a.first == "Tilesets")
			m_tileset_manager.mt_Load(m_resource_path + "Data/" + a.second);
		else if (a.first == "Maps")
			m_map_manager.mt_Load(m_resource_path + "Data/" + a.second, l_map_loaders, m_tileset_manager);
		else if (a.first == "Characters")
			m_character_manager.mt_Load(m_resource_path + "Data/" + a.second, l_character_loaders, m_skill_manager);
		else if (a.first == "Skills")
			m_skill_manager.mt_Load(m_resource_path + "Data/" + a.second, l_skill_loaders);
		else if (a.first == "Textures")
			m_texture_manager.mt_Load(m_resource_path + "Data/" + a.second);
	}
}
