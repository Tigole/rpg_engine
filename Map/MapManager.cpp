#include "MapManager.hpp"
#include "Exception/Exception.hpp"
#include "Miscellaneous.hpp"
#include "BasicMap.hpp"
#include <tinyxml.h>

void MapManager::load(const std::string& file_path, const std::map<std::string, std::unique_ptr<MapLoader>>& loaders, const TilesetManager& tm)
{
	TiXmlDocument l_doc;
	std::map<std::string, std::unique_ptr<MapLoader>>::const_iterator l_it;
	std::unique_ptr<IMap> l_map;

	if (l_doc.LoadFile(file_path) == false)
		throw ExceptionResourceDoesNotExists(file_path, FUNCTION_NAME);

	for (const TiXmlElement* l_child = l_doc.FirstChildElement("Maps")->FirstChildElement(); l_child != nullptr; l_child = l_child->NextSiblingElement())
	{
		l_it = loaders.find(l_child->ValueStr());
		if (l_it != loaders.end())
		{
			l_map = l_it->second.get()->load(*l_child, tm);
			m_data[l_map->getId()] = std::move(l_map);
		}
	}
}

IMap* MapManager::getMap(const std::string& map_id)
{
	std::map<std::string, std::unique_ptr<IMap>>::iterator l_it;

	l_it = m_data.find(map_id);
	if (l_it == m_data.end())
		throw ExceptionResourceDoesNotExists(map_id, FUNCTION_NAME);

	return l_it->second.get();
}