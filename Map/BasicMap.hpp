#ifndef _BASIC_MAP_HPP
#define _BASIC_MAP_HPP 1

#include "IMap.hpp"
#include "Tileset.hpp"
#include "Miscellaneous.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

class BasicMapLoader;
class MusicManager;
class TilesetManager;
class Environment;

class BasicMap : public IMap
{
public:
	BasicMap();// MusicManager* music_manager, TilesetManager* tileset_manager);
	BasicMap(const BasicMap& cp);
	~BasicMap();

	void mt_Save(TiXmlElement& element);
	const std::string& mt_Get_Id() const;
	void mt_Prepare(Environment& env);
	//std::unique_ptr<IMap> mt_Clone(void) const;

	void mt_Draw_Layer(int layer_number, sf::RenderWindow& window);
	const TileInfo* mt_Get_Tile_Infos(int x_index, int y_index, int elevation);
	const std::string& mt_Get_Ambiant_Music_Id(void) const;

	std::size_t mt_Get_Layer_Count(void) const;

	void mt_Unload(void);


	friend BasicMapLoader;

protected:
	struct LinkedMap
	{
		unsigned int m_col, m_row;
		std::string m_linked_map_name;
	};
	std::unordered_map<int, misc::Grid<Tile>> m_tiles;
	std::unordered_map<int, sf::RenderTexture> m_layers;
	std::vector<LinkedMap> m_linked_maps;
	std::string m_tileset_id;
	std::string m_ambiant_music_id;
	std::string m_id;
	TilesetManager* m_tileset_manager;
};

#endif // !_BASIC_MAP_HPP
