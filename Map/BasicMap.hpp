#ifndef _BASIC_MAP_HPP
#define _BASIC_MAP_HPP 1

#include "IMap.hpp"
#include "Tileset.hpp"
#include "Miscellaneous.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

class BasicMapLoader;

class BasicMap : public IMap
{
public:
	BasicMap();
	BasicMap(const BasicMap& cp);

	IMap* mt_Run(Environment& environment);
	void mt_Initialize(MapManager& map_manager);
	void mt_Save(TiXmlElement& element);
	const std::string& mt_Get_Id() const;
	std::unique_ptr<IMap> mt_Clone(void) const;

	void mt_Draw_Layer(int layer_number, sf::RenderWindow& window);
	const TileInfo* mt_Get_Tile_Infos(int x_index, int y_index, int elevation) const;


	friend BasicMapLoader;

protected:
	struct LinkedMap
	{
		unsigned int m_col, m_row;
		std::string m_linked_map_name;
	};
	std::map<int, misc::Grid<Tile>> m_tiles;
	std::map<int, sf::RenderTexture> m_layers;
	std::vector<LinkedMap> m_linked_maps;
	std::string m_ambiant_music;
	std::string m_id;
};

#endif // !_BASIC_MAP_HPP
