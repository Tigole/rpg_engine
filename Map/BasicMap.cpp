#include "BasicMap.hpp"
#include "TilesetManager.hpp"
#include "Environment.hpp"
#include <tinyxml.h>

#include "Logger/ILogger.h"


BasicMap::BasicMap()
	: m_background(),
	m_middleground(),
	m_foreground(),
	m_linked_maps(),
	m_ambiant_music()
{}

IMap* BasicMap::run(Environment& environment)
{
	sf::RenderWindow window(sf::VideoMode(640, 480), m_id);
	unsigned int l_col, l_row;
	
	window.setFramerateLimit(90);

	//environment.m_music_manager.play(m_ambiant_music);

	while (window.isOpen())
	{
		sf::Event event;
		sf::Vector2u size(m_background.size());
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Magenta);
		// puis, dans la boucle de dessin, entre window.clear() et window.display()

		for(l_col = 0; l_col < size.x; l_col++)
			for (l_row = 0; l_row < size.y; l_row++)
				window.draw(m_background[l_col][l_row]);

		window.draw(m_background[1][0]);

		//m_background[1][0].move(0.5, 0.5);

		window.display();
	}

	return nullptr;
}

void BasicMap::load(const TiXmlElement& element, const TilesetManager& tm)
{
	std::map<std::string, Grid<Tile>*> l_grounds;
	std::map<std::string, Grid<Tile>*>::iterator l_it;
	sf::Vector2u l_ground_size;
	unsigned int l_tile_width(32);
	unsigned int l_tile_heigt(32);
	unsigned int l_col, l_row;

	l_grounds["Background"] = &m_background;
	l_grounds["Middleground"] = &m_middleground;
	l_grounds["Foreground"] = &m_foreground;

	for (const TiXmlElement* l_child = element.FirstChildElement(); l_child != nullptr; l_child = l_child->NextSiblingElement())
	{
		l_it = l_grounds.find(l_child->Value());
		if (l_it != l_grounds.end())
		{
			loadGround(*l_child, tm, *l_it->second);
			l_ground_size = l_it->second->size();
			for (l_col = 0; l_col < l_ground_size.x; l_col++)
				for (l_row = 0; l_row < l_ground_size.y; l_row++)
				{
					(*l_it->second)[l_col][l_row].setPosition(l_col * l_tile_width, l_row * l_tile_heigt);
				}
		}
		else if (l_child->ValueStr() == "LinkedMaps")
		{
			loadLinkedMaps(*l_child);
		}
		else if (l_child->ValueStr() == "AmbiantMusic")
		{
			l_child->QueryStringAttribute("id", &m_ambiant_music);
		}
	}
}

void BasicMap::initialize(MapManager& map_manager)
{
	//
}

void BasicMap::save(TiXmlElement& element)
{}

const std::string& BasicMap::getId() const
{
	return m_id;
}

void BasicMap::loadGround(const TiXmlElement& element_ground, const TilesetManager& tm, Grid<Tile>& ground)
{
	std::vector<std::pair<std::string, unsigned int*>> l_attributes;
	unsigned int l_cell_col, l_cell_row, l_tileset_col, l_tileset_row;
	std::string l_tileset_id;

	l_attributes.push_back(std::make_pair("cell_col", &l_cell_col));
	l_attributes.push_back(std::make_pair("cell_row", &l_cell_row));
	l_attributes.push_back(std::make_pair("tileset_col", &l_tileset_col));
	l_attributes.push_back(std::make_pair("tileset_row", &l_tileset_row));

	for (const TiXmlElement* l_cell = element_ground.FirstChildElement("Cell"); l_cell != nullptr; l_cell = l_cell->NextSiblingElement("Cell"))
	{
		for (auto& a : l_attributes)
			l_cell->QueryUnsignedAttribute(a.first.c_str(), a.second);
		l_cell->QueryValueAttribute("tileset_id", &l_tileset_id);

		ground.insert(l_cell_col - 1, l_cell_row - 1, tm.getTile(l_tileset_id, l_tileset_col - 1, l_tileset_row - 1));
	}
}

void BasicMap::loadLinkedMaps(const TiXmlElement& linked_maps)
{
	for (const TiXmlElement* l_child = linked_maps.FirstChildElement("LinkedMap"); l_child != nullptr; l_child = l_child->NextSiblingElement("LinkedMap"))
	{
		//
	}
}
