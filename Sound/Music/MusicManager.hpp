#ifndef _MUSIC_MANAGER_HPP
#define _MUSIC_MANAGER_HPP 1

#include <string>
#include <map>
#include <SFML/Audio.hpp>

#include "ResourceManager.hpp"

class MusicManager : public ResourceManager<MusicManager, sf::Music>
{
public:
	MusicManager(const std::string& resources_path)
		:ResourceManager<MusicManager, sf::Music>(resources_path, "/Musics/Music")
	{}

	bool mt_Load(sf::Music* resource, const std::string& file_path)
	{
		return resource->openFromFile(file_path);
	}
};

#if 0
struct MusicData
{
	MusicData();
	MusicData(const std::string& file_path, bool loop, float volume);
	std::string m_file_path;
	bool m_loop;
	float m_volume;
};

class MusicManager
{
public:
	MusicManager(const std::string& resource_path);
	void mt_Play(const std::string& music_id);
	void mt_Resume(void);
	void mt_Stop(void);
	void mt_Pause(void);
	void mt_Load(const std::string& file_path);

protected:
	std::string m_resource_path;
	std::map<std::string, MusicData> m_database;
	sf::Music m_music;
};

#endif

#endif // _MUSIC_MANAGER_HPP
