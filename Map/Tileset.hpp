#ifndef _TILESET_HPP
#define _TILESET_HPP 1

#include <SFML\Graphics.hpp>

class TiXmlElement;
class TextureManager;

struct Tile
{
	sf::Sprite m_sprite;
	bool m_is_walkable;
};

class Tileset
{
public:
	void load(const TiXmlElement& tileset, TextureManager& texture_manager);

	Tile getSprite(unsigned int x, unsigned int y);
protected:
	std::vector<std::vector<Tile>> m_tiles;
};

#endif // !_TILESET_HPP
