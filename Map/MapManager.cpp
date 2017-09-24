#include "MapManager.hpp"
#include "Exception/Exception.hpp"
#include "Miscellaneous.hpp"
#include "BasicMap.hpp"
#include <tinyxml.h>
#include "XMLFileLoader.hpp"
#include <SFML/System.hpp>

void MapManager::mt_Load(const std::string& file_path, const std::map<std::string, std::unique_ptr<IMapLoader>>& loaders, const TilesetManager& tm)
{
	TiXmlDocument l_doc;
	std::map<std::string, std::unique_ptr<IMapLoader>>::const_iterator l_it;
	std::unique_ptr<IMap> l_map;
	XMLFileLoader l_file_loader;

	if (l_doc.LoadFile(file_path) == false)
		throw ExceptionResourceDoesNotExists(file_path, FUNCTION_NAME);

	l_it = loaders.find(file_path);
	if (l_it == loaders.end())
		throw ExceptionXMLLoadingNoLoader(file_path);

	l_it->second->mt_Prepare(l_file_loader, file_path);

	l_file_loader.mt_Start();

	while (l_file_loader.mt_Is_Done() == false)
	{
		sf::sleep(sf::milliseconds(50));
	}

	l_map = l_it->second->mt_Get_Map();
	if (l_map == nullptr)
		throw Exception("Loading map failed : " + file_path);

	m_data[l_map->mt_Get_Id()] = std::move(l_map);
}

IMap* MapManager::mt_Get_Map(const std::string& map_id)
{
	std::map<std::string, std::unique_ptr<IMap>>::iterator l_it;

	l_it = m_data.find(map_id);
	if (l_it == m_data.end())
		throw ExceptionResourceDoesNotExists(map_id, FUNCTION_NAME);

	return l_it->second.get();
}
