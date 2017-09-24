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
	void mt_Load(const std::string& file_path, const std::map<std::string, std::unique_ptr<IMapLoader>>& loaders, const TilesetManager& tm);
	IMap* mt_Get_Map(const std::string& map_id);

private:
	std::map<std::string, std::unique_ptr<IMap>> m_data;
};

#endif // !_MAP_MANAGER_HPP
