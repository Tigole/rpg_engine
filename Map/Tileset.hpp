#ifndef _TILESET_HPP
#define _TILESET_HPP 1

#include "Loader/Loader.hpp"

#include <utility>

#include <SFML/Graphics.hpp>

class TiXmlElement;

struct TileInfo
{
	TileInfo()
		:m_is_walkable(true), m_friction(0.0f) {}
	TileInfo(bool is_walkable, float friction)
		:m_is_walkable(is_walkable), m_friction(friction) {}
	bool m_is_walkable;
	float m_friction;
};

struct Tile
{
	Tile();
	Tile(const Tile& cp);
	Tile& operator=(const Tile& cp);
	TileInfo m_infos;
	sf::Sprite m_sprite;
};

class Tileset : public ILoader
{
public:
	void mt_Load(const TiXmlElement& tileset, const std::string& resource_path);

	Tile mt_Get_Tile(unsigned int col, unsigned int row) const;
	const std::string& mt_Get_Id() const;
	sf::Vector2u mt_Get_Tile_Size(void) const;
protected:
	sf::Texture m_texture;
	int m_col_count;
	int m_row_count;
	bool m_default_walkable;
	std::vector<std::pair<int, int>> m_non_default_walkable_tile;
	std::string m_id;
};

#endif // !_TILESET_HPP
