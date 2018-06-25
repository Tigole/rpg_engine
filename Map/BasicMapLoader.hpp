#ifndef _BASIC_MAP_LOADER_HPP
#define _BASIC_MAP_LOADER_HPP 1

#include "BasicMap.hpp"
#include "MapLoader.hpp"

class XML_Element;
class ECS_EntityManager;

class BasicMapLoader : public MapLoader<BasicMap>
{
public:
	BasicMapLoader(TilesetManager* tileset_manager, ECS_EntityManager* entity_manager);
	~BasicMapLoader();

	virtual bool mt_Prepare_Loader(XMLFileLoader& file_loader, const std::string& file_path);
	bool mt_Finalize(void);

private:
	bool mt_Load_BasicMap(const XML_Element& basic_map);
	bool mt_Load_Layer(const XML_Element& layer);
	bool mt_Load_Cell(const XML_Element& cell);
	bool mt_Load_LinkedMap(const XML_Element& linked_map);
	bool mt_Load_AmbiantMusic(const XML_Element& ambiant_music);
	bool mt_Load_CharacterLayer(const XML_Element& character_layer);
	bool mt_Load_Entity(const XML_Element& entity);
	void mt_Unload_Map(void);

	ECS_EntityManager* m_entity_manager;
	TilesetManager* m_tileset_manager;
	std::pair<std::string, Tileset*> m_tileset;

	int m_current_layer;
};

#endif // !_BASIC_MAP_LOADER_HPP
