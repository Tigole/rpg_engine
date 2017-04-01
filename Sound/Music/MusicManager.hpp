#ifndef _MUSIC_MANAGER_HPP
#define _MUSIC_MANAGER_HPP 1

#include <string>
#include <map>
#include <SFML/Audio.hpp>

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
	void play(const std::string& music_id);
	void resume(void);
	void stop(void);
	void pause(void);
	void load(const std::string& file_path);

protected:
	std::string m_resource_path;
	std::map<std::string, MusicData> m_database;
	sf::Music m_music;
};

#endif // _MUSIC_MANAGER_HPP
