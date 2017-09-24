#ifndef _BASIC_MAP_LOADER_HPP
#define _BASIC_MAP_LOADER_HPP 1

#include "BasicMap.hpp"
#include "MapLoader.hpp"

class XML_Element;

class BasicMapLoader : public MapLoader<BasicMap>
{
public:
	BasicMapLoader(TilesetManager& tileset_manager);

	virtual void mt_Prepare(XMLFileLoader& file_loader, const std::string& file_path);

private:
	bool mt_Load_BasicMap(const XML_Element& basic_map);
	bool mt_Load_Layer(const XML_Element& layer);
	bool mt_Load_Cell(const XML_Element& cell);
	bool mt_Load_LinkedMap(const XML_Element& linked_map);
	bool mt_Load_AmbiantMusic(const XML_Element& ambiant_music);
	bool mt_Load_CharacterLayer(const XML_Element& character_layer);
	void mt_Unload_Map(void);
	void mt_Finalize(void);

	TilesetManager* m_tileset_manager;

	int m_current_layer;
	std::map<int, misc::Grid<Tile>> m_tiles;
};

#endif // !_BASIC_MAP_LOADER_HPP
