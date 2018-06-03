#ifndef _TILESET_HPP
#define _TILESET_HPP 1

#include "Loader/Loader.hpp"

#include <utility>
#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>

class TiXmlElement;

using TileId = unsigned int;

struct TileInfo
{
	TileInfo(){}
	sf::Vector2f m_friction;
	sf::Texture* m_texture;
	sf::IntRect m_texture_rect;
	TileId m_id;
	bool m_deadly;
};

struct Tile
{
	Tile();
	Tile(const Tile& cp);
	Tile& operator=(const Tile& cp);
	TileInfo* m_infos;
	bool m_is_solid;
};

class TilesetLoader;
class Tileset : public ILoader
{
public:
	TileInfo* mt_Get_Tile_Infos(TileId id);
	TileInfo* mt_Get_Tile_Infos(unsigned int col, unsigned int row);
	const std::string& mt_Get_Id() const;
	sf::Vector2u mt_Get_Tile_Size(void) const;
protected:
	friend TilesetLoader;
	bool mt_Add_Tile(TileId id, const sf::Vector2f& friction, bool deadly);
	bool mt_Col_Row_To_Id(unsigned int col, unsigned int row, TileId& id);
	bool mt_Id_To_Col_Row(TileId id, unsigned int& col, unsigned int& row);
	

	sf::Texture* m_texture;
	int m_col_count;
	int m_row_count;
	std::unordered_map<TileId, std::unique_ptr<TileInfo>> m_tile_infos;
	std::string m_id;
};

class XMLFileLoader;
class XML_Element;
class TextureManager;
class TilesetLoader
{
public:
	TilesetLoader(TextureManager& texture_manager);
	bool mt_Prepare(Tileset& target, XMLFileLoader& loader, const std::string& file_path);

private:
	bool mt_Load_Texture(const XML_Element& texture);
	bool mt_Load_Tiles(const XML_Element& tiles);
	bool mt_Load_Tile(const XML_Element& tile);

	Tileset* m_Target;
	TextureManager* m_Texture_Manager;
};

#endif // !_TILESET_HPP
