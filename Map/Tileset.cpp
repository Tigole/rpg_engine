#include "Tileset.hpp"
#include "Exception\Exception.hpp"
#include "Miscellaneous.hpp"

void Tileset::load(const TiXmlElement& tileset, TextureManager& texture_manager)
{
	std::vector<std::string> attributes;
	std::string texture_path;
	int pixel_size_x, pixel_size_y;

	attributes.push_back("id");
	attributes.push_back("texture_id");
	attributes.push_back("tile_size_pixel_x");
	attributes.push_back("tile_size_pixel_y");

	if (checkAttributes(tileset, attributes) == true)
	{
		tileset.QueryIntAttribute("tile_size_pixel_x", &pixel_size_x);
		tileset.QueryIntAttribute("tile_size_pixel_y", &pixel_size_y);
	}
}

Tile Tileset::getSprite(unsigned int x, unsigned int y)
{
	Tile l_ret;
	if ((x < m_tiles.size()) && (m_tiles.size() != 0))
	{
		if (y < m_tiles[x].size())
		{
			l_ret = m_tiles[x][y];
		}
		else
		{
			throw ExceptionArraySize(y, m_tiles[x].size(), "m_tiles[" + misc::numberToString(x) + "]", FUNCTION_NAME);
		}
	}
	else
	{
		throw ExceptionArraySize(x, m_tiles.size(), "m_tiles", FUNCTION_NAME);
	}
	return l_ret;
}