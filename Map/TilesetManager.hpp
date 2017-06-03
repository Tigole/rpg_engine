#ifndef _TILESET_MANAGER_HPP
#define _TILESET_MANAGER_HPP 1

#include <string>
#include <map>
#include "Tileset.hpp"

class TilesetManager
{
public:
	TilesetManager(const std::string& resource_path);
	void load(const std::string& file_path);
	
	Tile getTile(const std::string& tileset_id, unsigned int col, unsigned int row) const;
	sf::Vector2u getTileSize(const std::string& tileset_id) const;

private:
	std::map<std::string, Tileset>::const_iterator getTileset(const std::string& tileset_id, const std::string& calling_function) const;
	std::map<std::string, Tileset> m_tilesets;
	std::string m_resources_path;
};

#endif // _TILESET_MANAGER_HPP