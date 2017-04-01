#ifndef _ENVIRONMENT_HPP
#define _ENVIRONMENT_HPP 1

#include "Sound/Music/MusicManager.hpp"

struct Environment
{
	Environment(const std::string& resource_path)
		:m_music_manager(resource_path),
		m_tileset_manager(resource_path)
	{}
	MusicManager m_music_manager;
	TilesetManager m_tileset_manager;
};

#endif // !_ENVIRONMENT_HPP