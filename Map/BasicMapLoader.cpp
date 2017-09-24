#include "BasicMapLoader.hpp"
#include "BasicMap.hpp"
#include "TilesetManager.hpp"

#include "Loader/XMLAttributeLoader.hpp"

#include "XMLFileLoader.hpp"
#include "Environment.hpp"

BasicMapLoader::BasicMapLoader(TilesetManager& tileset_manager)
	:MapLoader<BasicMap>(),
	m_tileset_manager(&tileset_manager),
	m_current_layer(0)
{}

void BasicMapLoader::mt_Prepare(XMLFileLoader& file_loader, const std::string& file_path)
{
	m_current_layer = 0;
	file_loader.mt_Set_File(file_path);
	file_loader.mt_Add_On_Entry_Callback(file_path, "/BasicMap/Layer", &BasicMapLoader::mt_Load_Layer, this);
	file_loader.mt_Add_On_Entry_Callback(file_path, "/BasicMap/Layer/Cell", &BasicMapLoader::mt_Load_Cell, this);
	file_loader.mt_Add_On_Entry_Callback(file_path, "/BasicMap/LinkedMaps/LinkedMap", &BasicMapLoader::mt_Load_LinkedMap, this);
	file_loader.mt_Add_On_Entry_Callback(file_path, "/BasicMap/AmbiantMusic", &BasicMapLoader::mt_Load_AmbiantMusic, this);
	file_loader.mt_Add_On_Entry_Callback(file_path, "/BasicMap/CharacterLayer", &BasicMapLoader::mt_Load_CharacterLayer, this);
}

bool BasicMapLoader::mt_Load_BasicMap(const XML_Element& basic_map)
{
	bool l_b_ret;
	XMLAttributeLoaderList l_list(new XMLAttributeLoader<std::string>("id", m_map.m_id));

	l_b_ret = l_list.mt_Load(basic_map);

	return l_b_ret;
}

bool BasicMapLoader::mt_Load_Layer(const XML_Element& layer)
{
	bool l_b_ret;
	XMLAttributeLoaderList l_list(new XMLAttributeLoader<int>("number", m_current_layer));

	l_b_ret = l_list.mt_Load(layer);

	return l_b_ret;
}

bool BasicMapLoader::mt_Load_Cell(const XML_Element& cell)
{
	bool l_b_ret;
	XMLAttributeLoaderList l_list;
	unsigned int l_cell_col, l_cell_row, l_tileset_col, l_tileset_row;
	std::string l_tileset_id;
	sf::Vector2u l_tile_size;

	l_list.mt_Add(new XMLAttributeLoader<unsigned int>("cell_col", l_cell_col));
	l_list.mt_Add(new XMLAttributeLoader<unsigned int>("cell_row", l_cell_row));
	l_list.mt_Add(new XMLAttributeLoader<unsigned int>("tileset_col", l_tileset_col));
	l_list.mt_Add(new XMLAttributeLoader<unsigned int>("tileset_row", l_tileset_row));
	l_list.mt_Add(new XMLAttributeLoader<std::string>("tileset_id",l_tileset_id));

	l_b_ret = l_list.mt_Load(cell);

	if (l_b_ret == true)
	{
		l_tile_size = m_tileset_manager->mt_Get_Tile_Size(l_tileset_id);

		m_tiles[m_current_layer].mt_Insert(l_cell_col - 1, l_cell_row - 1, m_tileset_manager->mt_Get_Tile(l_tileset_id, l_tileset_col - 1, l_tileset_row - 1));
		m_tiles[m_current_layer][l_cell_col - 1][l_cell_row - 1].m_sprite.setPosition((l_cell_col - 1) * l_tile_size.x, (l_cell_row - 1) * l_tile_size.y);
	}

	return l_b_ret;
}

bool BasicMapLoader::mt_Load_LinkedMap(const XML_Element& linked_map)
{
	bool l_b_ret;
	BasicMap::LinkedMap l_linked_map;
	XMLAttributeLoaderList l_list(new XMLAttributeLoader<unsigned int>("cell_row", l_linked_map.m_row),
		new XMLAttributeLoader<unsigned int>("cell_col", l_linked_map.m_col),
		new XMLAttributeLoader<std::string>("map_id", l_linked_map.m_linked_map_name));

	l_b_ret = l_list.mt_Load(linked_map);

	if (l_b_ret == true)
		m_map.m_linked_maps.push_back(l_linked_map);

	return l_b_ret;
}

bool BasicMapLoader::mt_Load_AmbiantMusic(const XML_Element& ambiant_music)
{
	bool l_b_ret;
	XMLAttributeLoaderList l_list(new XMLAttributeLoader<std::string>("", m_map.m_ambiant_music));

	l_b_ret = l_list.mt_Load(ambiant_music);

	return l_b_ret;
}

bool BasicMapLoader::mt_Load_CharacterLayer(const XML_Element& character_layer)
{
	bool l_b_ret(true);
	return l_b_ret;
}

void BasicMapLoader::mt_Unload_Map(void)
{
	m_map.m_tiles.clear();
}

void BasicMapLoader::mt_Finalize(void)
{
	Environment l_env("");
	sf::Vector2u l_dimension_cell;
	sf::Vector2u l_dimension_pixels;

	log().mt_Entrance_Function(FUNCTION_NAME);

	for (auto l_it = m_tiles.begin(); l_it != m_tiles.end(); l_it++)	/** Create 1 image per layer to draw it in the screen **/
	{
		l_dimension_cell = l_it->second.mt_Size();

		l_dimension_pixels.x = l_dimension_cell.x * l_it->second[0][0].m_sprite.getTextureRect().width;
		l_dimension_pixels.y = l_dimension_cell.y * l_it->second[0][0].m_sprite.getTextureRect().height;

		m_map.m_layers[l_it->first].create(l_dimension_pixels.x, l_dimension_pixels.y);

		for (unsigned int l_col = 0; l_col < l_dimension_cell.x; l_col++)
			for (unsigned int l_row = 0; l_row < l_dimension_cell.y; l_row++)
			{
				m_map.m_layers[l_it->first].draw(l_it->second[l_col][l_row].m_sprite);
			}
	}

	log().mt_Exit_Function();
}
