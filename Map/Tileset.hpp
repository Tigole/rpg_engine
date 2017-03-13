#ifndef _TILESET_HPP
#define _TILESET_HPP 1

#include "Loader/Loader.hpp"

#include <SFML/Graphics.hpp>

class TiXmlElement;
class TextureManager;

struct Tile : public sf::Sprite
{
	bool m_is_walkable;
};

class Tileset : public ILoader
{
public:
	void load(const TiXmlElement& tileset, TextureManager& texture_manager);

	Tile getSprite(unsigned int x, unsigned int y);
protected:
	std::vector<std::vector<Tile>> m_tiles;
	std::string m_id;
};

#endif // !_TILESET_HPP
