#ifndef _SOUND_SYSTEM_HPP
#define _SOUND_SYSTEM_HPP 1

#include "Music/MusicManager.hpp"

struct MusicData
{
	bool m_loop;
	float m_volume;
};

class SoundSystem
{
public:
	SoundSystem(const std::string& resource_path);

	void mt_Play_Music(const std::string& music_id);
	void mt_Stop_Music(const std::string& music_id);
	void mt_Pause_Music(const std::string& music_id);

	void mt_Play_Sound(const std::string& sound_id);

	void mt_Music_Load_Resource_Paths(const std::string& conf_file);
	void mt_Sound_Load_Resource_Paths(const std::string& conf_file);

private:
	MusicManager m_music_manager;
	sf::Music* m_music;
};

#endif // !_SOUND_SYSTEM_HPP