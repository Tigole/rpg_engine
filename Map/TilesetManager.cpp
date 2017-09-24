#include "TilesetManager.hpp"
#include "Exception/Exception.hpp"
#include "Miscellaneous.hpp"
#include <tinyxml.h>

TilesetManager::TilesetManager(const std::string& resource_path)
	:	m_resources_path(resource_path)
{}

void TilesetManager::mt_Load(const std::string& file_path)
{
	TiXmlDocument l_doc(file_path);
	TiXmlElement* l_root(nullptr);

	if (l_doc.LoadFile() == false)
		throw ExceptionResourceDoesNotExists(file_path, FUNCTION_NAME);

	l_root = l_doc.FirstChildElement("Tilesets");
	for (auto a = l_root->FirstChildElement("Tileset"); a != nullptr; a = a->NextSiblingElement("Tileset"))
	{
		Tileset l_tileset;

		l_tileset.mt_Load(*a, m_resources_path);

		if (m_tilesets.find(l_tileset.mt_Get_Id()) != m_tilesets.end())
			throw ExceptionResourceAlradeyExists(l_tileset.mt_Get_Id(), FUNCTION_NAME);

		m_tilesets[l_tileset.mt_Get_Id()] = l_tileset;
	}


}

Tile TilesetManager::mt_Get_Tile(const std::string& tileset_id, unsigned int col, unsigned int row) const
{
	return mt_Get_Tileset(tileset_id, FUNCTION_NAME)->second.mt_Get_Tile(col, row);
}

sf::Vector2u TilesetManager::mt_Get_Tile_Size(const std::string& tileset_id) const
{
	return mt_Get_Tileset(tileset_id, FUNCTION_NAME)->second.mt_Get_Tile_Size();
}

std::map<std::string, Tileset>::const_iterator TilesetManager::mt_Get_Tileset(const std::string& tileset_id, const std::string& calling_function) const
{
	std::map<std::string, Tileset>::const_iterator l_it;

	l_it = m_tilesets.find(tileset_id);
	if (l_it == m_tilesets.end())
		throw ExceptionResourceDoesNotExists(tileset_id, calling_function);

	return l_it;
}
