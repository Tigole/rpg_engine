#ifndef _BASIC_MAP_HPP
#define _BASIC_MAP_HPP 1

#include "IMap.hpp"
#include "Tileset.hpp"

#include <SFML\Graphics.hpp>

#include <vector>

class BasicMap : public IMap
{
public:
	BasicMap();

	IMap* run();
	void load(const TiXmlElement& element, MapManager& map_manager);
	void save(TiXmlElement& element);

protected:
	std::vector<Tile> m_cells;
};

#endif // !_BASIC_MAP_HPP