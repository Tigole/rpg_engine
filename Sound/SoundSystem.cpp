#include "SoundSystem.hpp"


SoundSystem::SoundSystem(const std::string& resource_path)
	:m_music_manager(resource_path)
{}

void SoundSystem::mt_Play_Music(const std::string& music_id)
{
	m_music = m_music_manager.mt_Get_Resource(music_id);

	if (m_music != nullptr)
	{
		m_music->setLoop(true);
		m_music->play();
	}
}

void SoundSystem::mt_Stop_Music(const std::string& music_id)
{
	if (m_music != nullptr)
	{
		m_music->stop();
		m_music_manager.mt_Release_Resource(music_id);
	}
}

void SoundSystem::mt_Pause_Music(const std::string& music_id)
{
	if (m_music != nullptr)
	{
		m_music->pause();
	}
}

void SoundSystem::mt_Play_Sound(const std::string& sound_id)
{
	//
}


void SoundSystem::mt_Music_Load_Resource_Paths(const std::string& conf_file)
{
	m_music_manager.mt_Load_Resource_Paths(conf_file);
}

void SoundSystem::mt_Sound_Load_Resource_Paths(const std::string& conf_file)
{
	//
}
