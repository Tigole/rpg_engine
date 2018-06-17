#ifndef _MAP_MANAGER_HPP
#define _MAP_MANAGER_HPP 1

#include "MapLoader.hpp"
#include "Map/IMap.hpp"
#include "ResourceManager.hpp"

#include <string>
#include <map>
#include <memory>

class TilesetManager;
class Environment;

template<typename MapType, typename MapLoaderType>
class MapManager : public ResourceManager<MapManager<MapType, MapLoaderType>, MapType>
{
public:
	MapManager(const std::string& resource_path, TilesetManager* tileset_manager)
		:ResourceManager<MapManager<MapType, MapLoaderType>, MapType>(resource_path, "/Maps/Map"),
		m_tileset_manager(tileset_manager)
	{}
	virtual ~MapManager(){}
	bool mt_Load(MapType* resource, const std::string& file_path)
	{
		bool l_b_ret;
		MapLoaderType l_map_loader_type(m_tileset_manager);
		XMLFileLoader l_xml_loader;

		l_b_ret = l_map_loader_type.mt_Prepare(*resource, l_xml_loader, file_path);

		if (l_b_ret == true)
		{
			l_xml_loader.mt_Start();
			l_xml_loader.mt_Wait_For_Ending();
			l_map_loader_type.mt_Finalize();
		}

		return l_b_ret;
	}

protected:

	TilesetManager* m_tileset_manager;
};

#endif // !_MAP_MANAGER_HPP
