#include "GUI.hpp"

#include "GUI\TextureManager.hpp"
#include "Exception\Exception.hpp"
#include "Miscellaneous.hpp"

#include <iostream>
#include <map>

IGUIBackground::~IGUIBackground()
{
	/** Nothing **/
}

GUIBackground::GUIBackground()
{
	/** Nothing **/
}

GUIBackground::GUIBackground(TextureManager& texture_manager, 
	const std::string& texture_id,
	EdgeType edge_type,
	unsigned int edge_size_px, 
	unsigned int left_px, 
	unsigned int top_px, 
	unsigned int width_px, 
	unsigned int height_px)
{
	sf::Texture& texture(texture_manager.getTexture(texture_id));
	sf::Sprite background;
	sf::Sprite top_edge_sprite, right_edge_sprite, bottom_edge_sprite, left_edge_sprite;
	sf::Sprite top_left_corner_sprite, top_right_corner_sprite, bottom_right_corner_sprite, bottom_left_corner_sprite;
	unsigned int vertical_elements_count(3), horizontal_element_count(2);
	std::map<EdgeType, set_edge_function> set_edge_function_map;
	std::map<EdgeType, set_edge_function>::iterator it;

	set_edge_function_map[COPY] = &GUIBackground::setEdgeCopy;
	set_edge_function_map[SCALE] = &GUIBackground::setEdgeScale;

	set_edge_function_map.find(edge_type);

	background.setTexture(texture);
	background.setTextureRect(sf::IntRect(edge_size_px, edge_size_px, texture.getSize().x - (2*edge_size_px), texture.getSize().y - (2*edge_size_px)));

	top_left_corner_sprite.setTexture(texture);
	top_left_corner_sprite.setTextureRect(sf::IntRect(0, 0, edge_size_px, edge_size_px));
	top_right_corner_sprite.setTexture(texture);
	top_right_corner_sprite.setTextureRect(sf::IntRect(texture.getSize().x - edge_size_px, 0, edge_size_px, edge_size_px));
	bottom_right_corner_sprite.setTexture(texture);
	bottom_right_corner_sprite.setTextureRect(sf::IntRect(texture.getSize().x - edge_size_px, texture.getSize().y - edge_size_px, edge_size_px, edge_size_px));
	bottom_left_corner_sprite.setTexture(texture);
	bottom_left_corner_sprite.setTextureRect(sf::IntRect(0, texture.getSize().y - edge_size_px, edge_size_px, edge_size_px));

	top_edge_sprite.setTexture(texture);
	top_edge_sprite.setTextureRect(sf::IntRect(edge_size_px, 0, background.getTextureRect().width, edge_size_px));
	right_edge_sprite.setTexture(texture);
	right_edge_sprite.setTextureRect(sf::IntRect(texture.getSize().x - edge_size_px, edge_size_px, edge_size_px, texture.getSize().y - edge_size_px));
	bottom_edge_sprite.setTexture(texture);
	bottom_edge_sprite.setTextureRect(sf::IntRect(edge_size_px, texture.getSize().y - edge_size_px, background.getTextureRect().width, edge_size_px));
	left_edge_sprite.setTexture(texture);
	left_edge_sprite.setTextureRect(sf::IntRect(0, edge_size_px, edge_size_px, background.getTextureRect().height));

	resize(vertical_elements_count + 2, horizontal_element_count + 2);

	setBackground(background, edge_size_px);

	setCorners(top_left_corner_sprite,
		top_right_corner_sprite,
		bottom_right_corner_sprite,
		bottom_left_corner_sprite,
		horizontal_element_count,
		vertical_elements_count,
		sf::Vector2i(background.getTextureRect().width, background.getTextureRect().height));

	it = set_edge_function_map.find(edge_type);

	if (it == set_edge_function_map.end())
		throw ResourceDoesNotExists(misc::numberToString(edge_type), FUNCTION_NAME);

	(this->*(it->second))(top_edge_sprite,
		right_edge_sprite,
		bottom_edge_sprite,
		left_edge_sprite,
		horizontal_element_count,
		vertical_elements_count,
		sf::Vector2i(background.getTextureRect().width, background.getTextureRect().height));

	setScreenPosition(top_px, left_px);
}

void GUIBackground::setScreenPosition(int left_px, int top_px)
{
	int dx(0), dy(0);

	dx = left_px - m_background.front().front().getPosition().x;
	dy = top_px - m_background.front().front().getPosition().y;

	moveBy(dx, dy);
}

sf::Vector2u GUIBackground::getDimensions(void) const
{
	sf::Vector2u l_ret(0, 0);

	l_ret.x = (m_background.front().back().getTextureRect().width + m_background.front().back().getPosition().x) - m_background.front().front().getPosition().x;
	//l_ret.y = m_background.front().back().getTextureRect()->getSize().y - m_background.front().front().getPosition().y;

	return l_ret;
}

void GUIBackground::moveBy(int dx, int dy)
{
	for (auto& v : m_background)
		for (auto& s : v)
			s.move(dx, dy);
}

void GUIBackground::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (auto& v : m_background)
		for (auto& s : v)
			target.draw(s);
}

void GUIBackground::setBackground(sf::Sprite& sprite, unsigned int edge_size_px)
{
	unsigned int x, y;
	unsigned int sprite_width(0), sprite_height(0);

	sprite_width = sprite.getTextureRect().width;
	sprite_height = sprite.getTextureRect().height;

	for (x = 1; x < (m_background.size() - 1); x++)
	{
		for (y = 1; y < (m_background[x].size() - 1); y++)
		{
			m_background[x][y] = sprite;
			m_background[x][y].setPosition((x-1) * sprite_width + edge_size_px, (y-1) * sprite_height + edge_size_px);
		}
	}
}

void GUIBackground::setEdgeCopy(sf::Sprite& top_edge_sprite, 
								sf::Sprite& right_edge_sprite, 
								sf::Sprite& bottom_edge_sprite, 
								sf::Sprite& left_edge_sprite, 
								unsigned int horizontal_sub_lignes_count, 
								unsigned int vertical_sub_lignes_count, 
								sf::Vector2i background_sprite_size)
{
	unsigned int x, y;
	
	/** Top and bottom **/
	for (x = 1; x < (m_background.size() - 1); x++)
	{
		top_edge_sprite.setPosition((x - 1) * background_sprite_size.x + left_edge_sprite.getTextureRect().width, 0.0f);
		bottom_edge_sprite.setPosition((x - 1) * background_sprite_size.x + left_edge_sprite.getTextureRect().width, horizontal_sub_lignes_count * background_sprite_size.y + top_edge_sprite.getTextureRect().height);
		m_background[x][0] = top_edge_sprite;
		m_background[x].back() = bottom_edge_sprite;
	}

	for (y = 1; y < (m_background.front().size() - 1); y++)
	{
		left_edge_sprite.setPosition(0, (y - 1) * background_sprite_size.y + top_edge_sprite.getTextureRect().height);
		right_edge_sprite.setPosition(vertical_sub_lignes_count * background_sprite_size.x + left_edge_sprite.getTextureRect().width, (y - 1) * background_sprite_size.y + top_edge_sprite.getTextureRect().height);
		m_background[0][y] = left_edge_sprite;
		m_background[m_background.size() - 1][y] = right_edge_sprite;
	}
}

void GUIBackground::setEdgeScale(sf::Sprite& top_edge_sprite,
	sf::Sprite& right_edge_sprite,
	sf::Sprite& bottom_edge_sprite,
	sf::Sprite& left_edge_sprite,
	unsigned int horizontal_sub_lignes_count,
	unsigned int vertical_sub_lignes_count,
	sf::Vector2i background_sprite_size)
{
	top_edge_sprite.setScale(horizontal_sub_lignes_count * background_sprite_size.x, 1.0f);
	bottom_edge_sprite.setScale(horizontal_sub_lignes_count * background_sprite_size.x, 1.0f);
	right_edge_sprite.setScale(1.0f, vertical_sub_lignes_count * background_sprite_size.y);
	left_edge_sprite.setScale(1.0f, vertical_sub_lignes_count * background_sprite_size.y);

	top_edge_sprite.setPosition(left_edge_sprite.getTextureRect().width, 0.0f);
	bottom_edge_sprite.setPosition(left_edge_sprite.getTextureRect().width, horizontal_sub_lignes_count * background_sprite_size.y + top_edge_sprite.getTextureRect().height);

	m_background[1][0] = top_edge_sprite;
	m_background[0][1] = left_edge_sprite;
	m_background[1][m_background.front().size() - 1] = bottom_edge_sprite;
	m_background[0][m_background.size() - 1] = right_edge_sprite;
}

void GUIBackground::setCorners(	sf::Sprite& top_left_corner_sprite,
								sf::Sprite& top_right_corner_sprite,
								sf::Sprite& bottom_right_corner_sprite,
								sf::Sprite& bottom_left_corner_sprite, 
								unsigned int horizontal_sub_elements_count, 
								unsigned int vertical_sub_element_count, 
								sf::Vector2i background_sprite_size)
{
	unsigned int x_offset_px(top_left_corner_sprite.getTextureRect().width), y_offset_px(top_left_corner_sprite.getTextureRect().height);

	top_left_corner_sprite.setPosition(0, 0);
	m_background.front().front() = top_left_corner_sprite;

	top_right_corner_sprite.setPosition(vertical_sub_element_count * background_sprite_size.x + x_offset_px, 0);
	m_background.front().back() = top_right_corner_sprite;

	bottom_right_corner_sprite.setPosition(vertical_sub_element_count * background_sprite_size.x + x_offset_px, horizontal_sub_elements_count * background_sprite_size.y + y_offset_px);
	m_background.back().back() = bottom_right_corner_sprite;

	bottom_left_corner_sprite.setPosition(0, horizontal_sub_elements_count * background_sprite_size.y + y_offset_px);
	m_background.back().front() = bottom_left_corner_sprite;
}

void GUIBackground::resize(unsigned int new_size)
{
	resize(new_size, new_size);
}

void GUIBackground::resize(unsigned int x_size, unsigned int y_size)
{
	m_background.resize(x_size);
	for (auto& v : m_background)
		v.resize(y_size);
}