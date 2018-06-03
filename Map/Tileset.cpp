#include "Tileset.hpp"
#include "Exception/Exception.hpp"
#include "Miscellaneous.hpp"

Tile::Tile()
{}

Tile::Tile(const Tile& cp)
	: m_infos(cp.m_infos),
	m_is_solid(cp.m_is_solid)
{}

Tile& Tile::operator=(const Tile& cp)
{
	m_infos = cp.m_infos;
	m_is_solid = cp.m_is_solid;

	return *this;
}

const std::string& Tileset::mt_Get_Id() const
{
	return m_id;
}

TileInfo* Tileset::mt_Get_Tile_Infos(TileId id)
{
	TileInfo* l_ret;
	std::unordered_map<TileId, std::unique_ptr<TileInfo>>::const_iterator l_it;

	l_it = m_tile_infos.find(id);

	if (l_it != m_tile_infos.end())
	{
		l_ret = l_it->second.get();
	}
	else
	{
		l_ret = nullptr;
	}

	return l_ret;
}

TileInfo* Tileset::mt_Get_Tile_Infos(unsigned int col, unsigned int row)
{
	TileInfo* l_ret;
	TileId l_id;

	if (mt_Col_Row_To_Id(col, row, l_id) == true)
	{
		l_ret = mt_Get_Tile_Infos(l_id);
	}
	else
	{
		l_ret = nullptr;
	}

	return l_ret;
}

bool Tileset::mt_Col_Row_To_Id(unsigned int col, unsigned int row, TileId& id)
{
	bool l_b_ret;

	if ((col < m_col_count) && (row < m_row_count))
	{
		id = (row * m_col_count) + col;
		l_b_ret = true;
	}
	else
	{
		l_b_ret = false;
	}

	return l_b_ret;
}

bool Tileset::mt_Id_To_Col_Row(TileId id, unsigned int& col, unsigned int& row)
{
	bool l_b_ret;

	if (m_col_count != 0)
	{
		row = id / m_col_count;
		col = id - (row * m_col_count);

		if ((row < m_row_count) && (col < m_col_count))
		{
			l_b_ret = true;
		}
		else
		{
			l_b_ret = false;
		}
	}
	else
	{
		l_b_ret = false;
	}

	return l_b_ret;
}

sf::Vector2u Tileset::mt_Get_Tile_Size(void) const
{
	sf::Vector2u l_ret(0, 0);

	if (m_texture != nullptr)
		l_ret = m_texture->getSize();

	l_ret.x /= m_col_count;
	l_ret.y /= m_row_count;

	return l_ret;
}

bool Tileset::mt_Add_Tile(TileId id, const sf::Vector2f& friction, bool deadly)
{
	bool l_b_ret;
	std::unique_ptr<TileInfo> l_tile_info;
	unsigned int l_col, l_row;
	sf::Vector2u l_tile_dimension;

	if (m_tile_infos.find(id) == m_tile_infos.end())
	{
		l_tile_dimension = mt_Get_Tile_Size();
		l_tile_info.reset(new TileInfo());
		l_tile_info->m_id = id;
		l_tile_info->m_friction = friction;
		l_tile_info->m_deadly = deadly;
		l_tile_info->m_texture = m_texture;
		l_b_ret = mt_Id_To_Col_Row(id, l_col, l_row);
		l_tile_info->m_texture_rect.left = l_col * l_tile_dimension.x;
		l_tile_info->m_texture_rect.top = l_row * l_tile_dimension.y;
		l_tile_info->m_texture_rect.width = l_tile_dimension.x;
		l_tile_info->m_texture_rect.height = l_tile_dimension.y;
		if (l_b_ret == true)
			l_b_ret = m_tile_infos.emplace(std::make_pair(id, std::move(l_tile_info))).second;
	}
	else
	{
		l_b_ret = false;
	}

	return l_b_ret;
}

#include "GUI/TextureManager.hpp"
#include "XMLFileLoader.hpp"

TilesetLoader::TilesetLoader(TextureManager& texture_manager)
	:m_Target(nullptr),
	m_Texture_Manager(&texture_manager)
{}

bool TilesetLoader::mt_Prepare(Tileset& target, XMLFileLoader& loader, const std::string& file_path)
{
	bool l_b_ret;

	m_Target = &target;
	l_b_ret = loader.mt_Set_File(file_path);
	if (l_b_ret == true)
		l_b_ret = loader.mt_Add_On_Entry_Callback(file_path, "/Tileset/Texture", &TilesetLoader::mt_Load_Texture, this);
	if (l_b_ret == true)
		l_b_ret = loader.mt_Add_On_Entry_Callback(file_path, "/Tileset/Tiles", &TilesetLoader::mt_Load_Tiles, this);
	if (l_b_ret == true)
		l_b_ret = loader.mt_Add_On_Entry_Callback(file_path, "/Tileset/Tiles/Tile", &TilesetLoader::mt_Load_Tile, this);

	return l_b_ret;
}

bool TilesetLoader::mt_Load_Texture(const XML_Element& texture)
{
	bool l_b_ret;
	std::string l_texture_id;

	l_b_ret = texture.mt_Get_Attribute("id", l_texture_id);
	if (l_b_ret == true)
	{
		m_Target->m_texture = m_Texture_Manager->mt_Get_Resource(l_texture_id);
	}

	return l_b_ret;
}

bool TilesetLoader::mt_Load_Tiles(const XML_Element& tiles)
{
	bool l_b_ret;

	l_b_ret = tiles.mt_Get_Attribute("col_count", m_Target->m_col_count);
	if (l_b_ret == true)
		l_b_ret = tiles.mt_Get_Attribute("row_count", m_Target->m_row_count);

	return l_b_ret;
}

bool TilesetLoader::mt_Load_Tile(const XML_Element& tile)
{
	bool l_b_ret;
	TileId l_id;
	sf::Vector2f l_friction;
	bool l_deadly;

	l_b_ret = tile.mt_Get_Attribute("id", (unsigned int&)l_id);
	if (l_b_ret == true)
		l_b_ret = tile.mt_Get_Attribute("x_friction", l_friction.x);
	if (l_b_ret == true)
		l_b_ret = tile.mt_Get_Attribute("y_friction", l_friction.y);
	if (l_b_ret == true)
		l_b_ret = tile.mt_Get_Attribute("deadly", l_deadly);
	if (l_b_ret == true)
		l_b_ret = m_Target->mt_Add_Tile(l_id, l_friction, l_deadly);

	return l_b_ret;
}