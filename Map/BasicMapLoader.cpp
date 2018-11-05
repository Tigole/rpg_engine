#include "BasicMapLoader.hpp"
#include "BasicMap.hpp"
#include "TilesetManager.hpp"

#include "Loader/XMLAttributeLoader.hpp"

#include "XMLFileLoader.hpp"
#include "Environment.hpp"

#include "ECS_Game/ComponentPosition.hpp"
#include "ECS_Core/ECS_EntityManager.hpp"

BasicMapLoader::BasicMapLoader(TilesetManager* tileset_manager, ECS_EntityManager* entity_manager)
	:MapLoader<BasicMap>(),
	m_entity_manager(entity_manager),
	m_tileset_manager(tileset_manager),
	m_tileset("", nullptr),
	m_current_layer(0)
{}

BasicMapLoader::~BasicMapLoader()
{
}

bool BasicMapLoader::mt_Prepare_Loader(XMLFileLoader& file_loader, const std::string& file_path)
{
	bool l_b_ret;

	m_current_layer = 0;
	l_b_ret = file_loader.mt_Set_File(file_path);
	if (l_b_ret == true)
		l_b_ret = file_loader.mt_Add_On_Entry_Callback(file_path, "/BasicMap", &BasicMapLoader::mt_Load_BasicMap, this);
	if (l_b_ret == true)
		l_b_ret = file_loader.mt_Add_On_Entry_Callback(file_path, "/BasicMap/Layer", &BasicMapLoader::mt_Load_Layer, this);
	if (l_b_ret == true)
		l_b_ret = file_loader.mt_Add_On_Entry_Callback(file_path, "/BasicMap/Layer/Cell", &BasicMapLoader::mt_Load_Cell, this);
	if (l_b_ret == true)
		l_b_ret = file_loader.mt_Add_On_Entry_Callback(file_path, "/BasicMap/LinkedMaps/LinkedMap", &BasicMapLoader::mt_Load_LinkedMap, this);
	if (l_b_ret == true)
		l_b_ret = file_loader.mt_Add_On_Entry_Callback(file_path, "/BasicMap/AmbiantMusic", &BasicMapLoader::mt_Load_AmbiantMusic, this);
	if (l_b_ret == true)
		l_b_ret = file_loader.mt_Add_On_Entry_Callback(file_path, "/BasicMap/CharacterLayer", &BasicMapLoader::mt_Load_CharacterLayer, this);
	if (l_b_ret == true)
		l_b_ret = file_loader.mt_Add_On_Entry_Callback(file_path, "/BasicMap/Entities/Entity", &BasicMapLoader::mt_Load_Entity, this);

	return l_b_ret;
}

bool BasicMapLoader::mt_Load_BasicMap(const XML_Element& basic_map)
{
	bool l_b_ret;
	XMLAttributeLoaderList l_list(new XMLAttributeLoader<std::string>("id", m_Target->m_id),
								  new XMLAttributeLoader<std::string>("tileset_id", m_tileset.first));

	l_b_ret = l_list.mt_Load(basic_map);

	if (l_b_ret == true)
	{
		m_Target->m_tileset_id = m_tileset.first;
		m_tileset.second = m_tileset_manager->mt_Get_Resource(m_tileset.first);
		l_b_ret = m_tileset.second != nullptr;
	}

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
	unsigned int l_cell_col, l_cell_row, l_tile_id;
	sf::Vector2u l_tile_size;

	l_list.mt_Add(new XMLAttributeLoader<unsigned int>("cell_col", l_cell_col));
	l_list.mt_Add(new XMLAttributeLoader<unsigned int>("cell_row", l_cell_row));
	l_list.mt_Add(new XMLAttributeLoader<unsigned int>("tile_id", l_tile_id));

	l_b_ret = l_list.mt_Load(cell);

	if (l_b_ret == true)
	{
		l_tile_size = m_tileset.second->mt_Get_Tile_Size();

		m_Target->m_tiles[m_current_layer].mt_Insert(l_cell_col, l_cell_row, Tile());
		m_Target->m_tiles[m_current_layer][l_cell_col][l_cell_row].m_infos = m_tileset.second->mt_Get_Tile_Infos(l_tile_id);
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
		m_Target->m_linked_maps.push_back(l_linked_map);

	l_b_ret = true;

	return l_b_ret;
}

bool BasicMapLoader::mt_Load_AmbiantMusic(const XML_Element& ambiant_music)
{
	bool l_b_ret;
	XMLAttributeLoaderList l_list(new XMLAttributeLoader<std::string>("id", m_Target->m_ambiant_music_id));

	l_b_ret = l_list.mt_Load(ambiant_music);

	l_b_ret = true;

	return l_b_ret;
}

bool BasicMapLoader::mt_Load_CharacterLayer(const XML_Element& character_layer)
{
	bool l_b_ret(true);
	return l_b_ret;
}

void BasicMapLoader::mt_Unload_Map(void)
{
	m_Target->m_tiles.clear();
}

bool BasicMapLoader::mt_Finalize(void)
{
	sf::Vector2u l_dimension_cell;
	sf::Vector2u l_dimension_pixels;
	sf::Sprite l_sprite;
	sf::Texture* l_texture;
	const TileInfo* l_tile_infos;
	sf::RenderWindow l_window(sf::VideoMode(128, 128), "toto");
	sf::Event l_event;

	log().mt_Entrance_Function(FUNCTION_NAME);

	for (auto l_it = m_Target->m_tiles.begin(); l_it != m_Target->m_tiles.end(); l_it++)	/** Create 1 image per layer to draw it in the screen **/
	{
		l_dimension_cell = l_it->second.mt_Size();
		
		l_dimension_pixels.x = l_dimension_cell.x * m_tileset.second->mt_Get_Tile_Size().x;
		l_dimension_pixels.y = l_dimension_cell.y * m_tileset.second->mt_Get_Tile_Size().y;

		m_Target->m_layers[l_it->first].create(l_dimension_pixels.x, l_dimension_pixels.y);

		for (unsigned int l_col = 0; l_col < l_dimension_cell.x; l_col++)
		{
			for (unsigned int l_row = 0; l_row < l_dimension_cell.y; l_row++)
			{
				l_tile_infos = l_it->second[l_col][l_row].m_infos;
				if (l_tile_infos != nullptr)
				{
					l_texture = l_tile_infos->m_texture;
					if (l_texture != nullptr)
					{
						l_sprite.setTexture(*l_texture);
						l_sprite.setTextureRect(l_tile_infos->m_texture_rect);
						l_sprite.setPosition(l_col * m_tileset.second->mt_Get_Tile_Size().x, l_row * m_tileset.second->mt_Get_Tile_Size().y);
						l_window.draw(l_sprite);
						m_Target->m_layers[l_it->first].draw(l_sprite);
					}
				}
			}
		}
		m_Target->m_layers[l_it->first].display();
	}

	m_Target->m_tileset_manager = m_tileset_manager;

	log().mt_Exit_Function();

	return true;
}

bool BasicMapLoader::mt_Load_Entity(const XML_Element& entity)
{
	bool l_b_ret;
	std::string l_id;
	sf::Vector2f l_pos;
	int l_layer;
	ECS_EntityId l_entity;
	ComponentPosition* l_position;

	l_b_ret = entity.mt_Get_Attribute("id", l_id);
	if (l_b_ret == true)
	{
		l_b_ret = entity.mt_Get_Attribute("x", l_pos.x);
	}
	if (l_b_ret == true)
	{
		l_b_ret = entity.mt_Get_Attribute("y", l_pos.y);
	}
	if (l_b_ret == true)
	{
		l_b_ret = entity.mt_Get_Attribute("z", l_layer);
	}
	if (l_b_ret == true)
	{
		sf::Vector2u l_Tile_Size;
		l_entity = m_entity_manager->mt_Get_Entity(l_id);

		l_position = m_entity_manager->mt_Get_Component<ComponentPosition>(l_entity, ECS_ComponentId::POSITION);

		l_Tile_Size = m_tileset.second->mt_Get_Tile_Size();

		l_pos.x = l_pos.x * l_Tile_Size.x + l_Tile_Size.x / 2;
		l_pos.y = l_pos.y * l_Tile_Size.y + 3 * l_Tile_Size.y / 4;

		l_position->mt_Set_Current_Position(l_pos, l_layer);
	}

	return l_b_ret;
}