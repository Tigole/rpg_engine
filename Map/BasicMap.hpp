#ifndef _BASIC_MAP_HPP
#define _BASIC_MAP_HPP 1

#include "IMap.hpp"
#include "Tileset.hpp"

#include <SFML\Graphics.hpp>

#include <vector>

template<typename T>
class Grid
{
public:
	Grid() : m_data(){}
	Grid(const Grid& cp) : m_data(cp.m_data){}
	void insert(unsigned int col, unsigned int row, const T& data)
	{
		unsigned int l_col(m_data.size()), l_row(0);
		if (m_data.size() != 0)
			l_row = m_data[0].size();
		if ((l_col == 0) && (l_row == 0))
		{
			l_col = 1;
			l_row = 1;
			resize(l_col, l_row);
		}
		if ((col >= l_col) || (row >= l_row))
		{
			if (col >= l_col)
				l_col = col + 1;
			if (row >= l_row)
				l_row = row + 1;
			resize(l_col, l_row);
		}
		m_data[col][row] = data;
	}
	std::vector<T>& operator[](unsigned int col)
	{
		return m_data[col];
	}
	sf::Vector2u size()
	{
		sf::Vector2u l_ret(0, 0);

		l_ret.x = m_data.size();
		if (l_ret.x != 0)
			l_ret.y = m_data[0].size();

		return l_ret;
	}
private:
	void resize(unsigned int col, unsigned int row)
	{
		m_data.resize(col);
		for (auto& a : m_data)
		{
			a.resize(row);
		}
	}
	std::vector<std::vector<T>> m_data;
};

class BasicMap : public IMap
{
public:
	BasicMap();

	IMap* run(Environment& environment);
	void load(const TiXmlElement& element, const TilesetManager& tm);
	void initialize(MapManager& map_manager);
	void save(TiXmlElement& element);
	const std::string& getId() const;
	std::unique_ptr<IMap> clone(void) const;

protected:
	void loadGround(const TiXmlElement& element_ground, const TilesetManager& tm, Grid<Tile>& ground);
	void loadLinkedMaps(const TiXmlElement& linked_maps);
	struct LinkedMap
	{
		unsigned int m_col, m_row;
		std::string m_linked_map_name;
	};
	Grid<Tile> m_background;
	Grid<Tile> m_middleground;
	Grid<Tile> m_foreground;
	std::vector<LinkedMap> m_linked_maps;
	std::string m_ambiant_music;
	std::string m_id;
};

#endif // !_BASIC_MAP_HPP