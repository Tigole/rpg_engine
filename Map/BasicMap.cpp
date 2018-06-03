#include "BasicMap.hpp"
#include "TilesetManager.hpp"
#include "Environment.hpp"
#include <tinyxml.h>

#include "Logger/ILogger.h"


BasicMap::BasicMap()//MusicManager* music_manager, TilesetManager* tileset_manager)
	: m_tiles(),
	m_linked_maps(),
	m_ambiant_music_id(),
	m_tileset_manager(nullptr)
{}

BasicMap::BasicMap(const BasicMap& cp)
	: m_tiles(cp.m_tiles),
	m_linked_maps(cp.m_linked_maps),
	m_ambiant_music_id(cp.m_ambiant_music_id),
	m_tileset_manager(cp.m_tileset_manager)
{}

BasicMap::~BasicMap()
{
	mt_Unload();
}

void BasicMap::mt_Draw_Layer(int layer_number, sf::RenderWindow& window)
{
	std::unordered_map<int, sf::RenderTexture>::const_iterator l_layer;
	sf::Sprite l_sprite;

	l_layer = m_layers.find(layer_number);

	if (l_layer != m_layers.end())
	{
		l_sprite.setTexture(l_layer->second.getTexture());
		l_sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(l_layer->second.getSize())));

		window.draw(l_sprite);
	}
}

void BasicMap::mt_Save(TiXmlElement& element)
{}

const std::string& BasicMap::mt_Get_Id() const
{
	return m_id;
}

/*std::unique_ptr<IMap> BasicMap::mt_Clone(void) const
{
	return std::unique_ptr<IMap>(new BasicMap(*this));
}*/

const TileInfo* BasicMap::mt_Get_Tile_Infos(int x_index, int y_index, int elevation)
{
	const TileInfo* l_ret(nullptr);
	std::unordered_map<int, misc::Grid<Tile>>::iterator l_it;

	l_it = m_tiles.find(elevation);

	if ((l_it != m_tiles.end()) && (x_index < l_it->second.mt_Size().x ) && (y_index < l_it->second.mt_Size().y))
	{
		l_ret = l_it->second.mt_At(x_index, y_index).m_infos;
	}

	return l_ret;
}

const std::string& BasicMap::mt_Get_Ambiant_Music_Id(void) const
{
	return m_ambiant_music_id;
}

std::size_t BasicMap::mt_Get_Layer_Count(void) const
{
	return m_layers.size();
}

void BasicMap::mt_Unload(void)
{
	m_tileset_manager->mt_Release_Resource(m_tileset_id);
}