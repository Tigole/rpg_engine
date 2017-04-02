#ifndef _MAP_MANAGER_HPP
#define _MAP_MANAGER_HPP 1

#include "MapLoader.hpp"
#include "Map/IMap.hpp"

#include <string>
#include <map>
#include <memory>

class TilesetManager;

class MapManager
{
public:
	void load(const std::string& file_path, const std::map<std::string, std::unique_ptr<MapLoader>>& loaders, const TilesetManager& tm);
	IMap* getMap(const std::string& map_id);

private:
	std::map<std::string, std::unique_ptr<IMap>> m_data;
};

#endif // !_MAP_MANAGER_HPP