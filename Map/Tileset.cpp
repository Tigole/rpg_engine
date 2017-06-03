#include "Tileset.hpp"
#include "Exception\Exception.hpp"
#include "Miscellaneous.hpp"

Tile::Tile()
	:m_is_walkable(true)
{}

Tile::Tile(const Tile& cp)
	: sf::Sprite(cp),
	m_is_walkable(cp.m_is_walkable)
{
	setPosition(cp.getPosition());
	/*const sf::Texture* l_texture(cp.getTexture());
	//setTextureRect(cp.getTextureRect());
	if (l_texture != nullptr)
		setTexture(*l_texture);*/
}

Tile& Tile::operator=(const Tile& cp)
{
	const sf::Texture* l_texture(cp.getTexture());

	if (l_texture != nullptr)
		setTexture(*l_texture);
	setTextureRect(cp.getTextureRect());
	setPosition(cp.getPosition());
	m_is_walkable = cp.m_is_walkable;

	return *this;
}

void Tileset::load(const TiXmlElement& tileset, const std::string& resource_path)
{
	std::vector<std::string> l_attributes;
	std::string l_texture_path;

	l_attributes.push_back("id");
	l_attributes.push_back("path");
	l_attributes.push_back("col_count");
	l_attributes.push_back("row_count");
	l_attributes.push_back("default_walkable");

	if (checkAttributes(tileset, l_attributes) == false)
		throw ExceptionXMLLoadingAttributeMissing(tileset, "");

	tileset.QueryStringAttribute("id", &m_id);
	tileset.QueryStringAttribute("path", &l_texture_path);
	tileset.QueryIntAttribute("col_count", &m_col_count);
	tileset.QueryIntAttribute("row_count", &m_row_count);
	tileset.QueryBoolAttribute("default_walkable", &m_default_walkable);

	if (m_texture.loadFromFile(resource_path + l_texture_path) == false)
		throw ExceptionResourceDoesNotExists(resource_path + l_texture_path, FUNCTION_NAME);

	l_attributes.resize(2);
	l_attributes[0] = "col";
	l_attributes[1] = "raw";

	for (auto l_child_element = tileset.FirstChildElement("NonDefaultWalkableTile"); l_child_element != nullptr; l_child_element = l_child_element->NextSiblingElement("NonDefaultWalkableTile"))
	{
		int l_col, l_row;
		if (checkAttributes(*l_child_element, l_attributes) == false)
			throw ExceptionXMLLoadingAttributeMissing(*l_child_element, "");
		m_non_default_walkable_tile.push_back(std::make_pair(l_col, l_row));
	}
}

const std::string& Tileset::getId() const
{
	return m_id;
}

Tile Tileset::getTile(unsigned int col, unsigned int row) const
{
	Tile l_ret;
	sf::Vector2u l_texture_size;
	int l_left, l_top, l_width, l_height;
	bool l_is_non_default_walkable(false);

	l_texture_size = m_texture.getSize();

	if ((l_texture_size.x / m_col_count >= col)
		&& (l_texture_size.y / m_row_count >= row))
	{
		l_width = l_texture_size.x / m_col_count;
		l_height = l_texture_size.y / m_row_count;
		l_left = col * l_width;
		l_top = row * l_height;
		l_ret.setTexture(m_texture);
		l_ret.setTextureRect(sf::IntRect(l_left, l_top, l_width, l_height));

		for (const auto& a : m_non_default_walkable_tile)
			if ((a.first == col) && (a.second == row))
				l_is_non_default_walkable = true;

		if (l_is_non_default_walkable)
			l_ret.m_is_walkable = m_default_walkable;
		else
			l_ret.m_is_walkable = !m_default_walkable;
	}
	else
		throw Exception("[" + misc::numberToString(col) + " " + misc::numberToString(row) +"] can't be acceded for tileset \"" + m_id + "\" in " + FUNCTION_NAME);

	return l_ret;
}

sf::Vector2u Tileset::getTileSize(void) const
{
	sf::Vector2u l_ret(m_texture.getSize());
	
	l_ret.x /= m_col_count;
	l_ret.y /= m_row_count;
	
	return l_ret;
}