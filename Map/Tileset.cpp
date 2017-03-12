#include "Tileset.hpp"
#include "Exception\Exception.hpp"
#include "Miscellaneous.hpp"

void Tileset::load(const TiXmlElement& tileset, TextureManager& texture_manager)
{
	//
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