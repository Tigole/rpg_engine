#ifndef _TILESET_HPP
#define _TILESET_HPP 1

#include "Loader/Loader.hpp"

#include <utility>

#include <SFML/Graphics.hpp>

class TiXmlElement;

struct Tile : public sf::Sprite
{
	Tile();
	Tile(const Tile& cp);
	bool m_is_walkable;
};

class Tileset : public ILoader
{
public:
	void load(const TiXmlElement& tileset, const std::string& resource_path);

	Tile getTile(unsigned int col, unsigned int row) const;
	const std::string& getId() const;
protected:
	sf::Texture m_texture;
	int m_col_count;
	int m_row_count;
	bool m_default_walkable;
	std::vector<std::pair<int, int>> m_non_default_walkable_tile;
	std::string m_id;
};

#endif // !_TILESET_HPP
