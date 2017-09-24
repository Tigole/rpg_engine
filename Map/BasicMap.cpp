#include "BasicMap.hpp"
#include "TilesetManager.hpp"
#include "Environment.hpp"
#include <tinyxml.h>

#include "Logger/ILogger.h"


BasicMap::BasicMap()
	: m_tiles(),
	m_linked_maps(),
	m_ambiant_music()
{}

BasicMap::BasicMap(const BasicMap& cp)
	: m_tiles(),
	m_linked_maps(cp.m_linked_maps),
	m_ambiant_music(cp.m_ambiant_music)
{
	for (auto l_it = cp.m_layers.begin(); l_it != cp.m_layers.end(); l_it++)
	{
		sf::Sprite l_sprite;

		l_sprite.setTexture(l_it->second.getTexture());
		m_layers[l_it->first].create(l_it->second.getTexture().getSize().x, l_it->second.getTexture().getSize().y);
		m_layers[l_it->first].draw(l_sprite);
	}
}

IMap* BasicMap::mt_Run(Environment& environment)
{
	sf::RenderWindow window(sf::VideoMode(640, 480), m_id);
	unsigned int l_col, l_row;
	float l_scale(1.0f);

	window.setFramerateLimit(5);

	environment.m_music_manager.mt_Play(m_ambiant_music);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseWheelMoved)
			{
				int delta(event.mouseWheel.delta);
				if (	(l_scale > 0.5f && delta < 0)
					||	(delta > 0 && l_scale < 3.0f))
					l_scale += delta * 0.5f;
			}
		}

		window.clear(sf::Color::Magenta);

		sf::Sprite l_sprite;

		l_sprite.setTexture(m_layers.begin()->second.getTexture());
		l_sprite.setScale(l_scale, l_scale);

		window.draw(l_sprite);

		window.display();
	}

	return nullptr;
}

void BasicMap::mt_Initialize(MapManager& map_manager)
{
	//
}

void BasicMap::mt_Save(TiXmlElement& element)
{}

const std::string& BasicMap::mt_Get_Id() const
{
	return m_id;
}

std::unique_ptr<IMap> BasicMap::mt_Clone(void) const
{
	return std::unique_ptr<IMap>(new BasicMap(*this));
}

const TileInfo* BasicMap::mt_Get_Tile_Infos(int x_index, int y_index, int elevation) const
{
	const TileInfo* l_ret(nullptr);
	std::map<int, misc::Grid<Tile>>::const_iterator l_it;

	l_it = m_tiles.find(elevation);

	if ((l_it != m_tiles.end()) && (x_index < l_it->second.mt_Size().x ) && (y_index < l_it->second.mt_Size().y))
	{
		l_ret = &l_it->second.mt_At(x_index, y_index).m_infos;
	}

	return l_ret;
}