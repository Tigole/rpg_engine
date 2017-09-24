#include "MusicManager.hpp"
#include "Exception/Exception.hpp"
#include "Miscellaneous.hpp"
#include <tinyxml.h>

MusicData::MusicData()
	: m_file_path(),
	m_loop(true),
	m_volume(100.0f)
{}

MusicData::MusicData(const std::string& file_path, bool loop, float volume)
	: m_file_path(file_path),
	m_loop(loop),
	m_volume(volume)
{
	if (m_volume < 0.0f)
		m_volume = 0.0f;
	if (m_volume > 100.0f)
		m_volume = 100.0f;
}

MusicManager::MusicManager(const std::string& resource_path)
	:	m_resource_path(resource_path),
	m_database()
{}

void MusicManager::mt_Play(const std::string& music_id)
{
	std::map<std::string, MusicData>::iterator l_it;

	l_it = m_database.find(music_id);

	if (l_it != m_database.end())
	{
		m_music.openFromFile(m_resource_path + l_it->second.m_file_path);
		m_music.setLoop(true);
		m_music.play();
	}
}

void MusicManager::mt_Resume(void)
{
	if (m_music.getStatus() == sf::Music::Paused)
		m_music.play();
}

void MusicManager::mt_Stop(void)
{
	m_music.stop();
}

void MusicManager::mt_Pause(void)
{
	m_music.pause();
}

void MusicManager::mt_Load(const std::string& file_path)
{
	TiXmlDocument l_doc;
	std::string l_id, l_path;
	std::vector<std::pair<std::string, std::string*>> l_attributes;
	TiXmlHandle l_handle(&l_doc);
	bool l_loop(true);
	float l_volume(100.0f);

	if (!l_doc.LoadFile(file_path))
		throw ExceptionResourceDoesNotExists(file_path, FUNCTION_NAME);

	l_attributes.push_back(std::make_pair("id", &l_id));
	l_attributes.push_back(std::make_pair("path", &l_path));

	for (const TiXmlElement* l_child = l_handle.FirstChildElement("Musics").FirstChildElement("Music").Element(); l_child != nullptr; l_child = l_child->NextSiblingElement("Music"))
	{
		l_loop = true;
		l_volume = 100.0f;
		for (const auto& a : l_attributes)
			l_child->QueryValueAttribute(a.first, a.second);
		l_child->QueryValueAttribute("id", &l_id);
		l_child->QueryBoolAttribute("loop", &l_loop);
		l_child->QueryFloatAttribute("volume", &l_volume);

		if (m_database.find(l_id) != m_database.end())
			throw ExceptionResourceAlradeyExists(l_id, FUNCTION_NAME);

		m_database[l_id] = MusicData(l_path, l_loop, l_volume);
	}
}
