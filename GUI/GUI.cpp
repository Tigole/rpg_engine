#include "GUI.hpp"

#include "GUI/TextureManager.hpp"
#include "Exception/Exception.hpp"
#include "Miscellaneous.hpp"

#include <iostream>
#include <map>

IGUIBackground::~IGUIBackground()
{
	/** Nothing **/
}

GUIBackground::TextureData::TextureData()
	:m_top_edge_size_px(0),
	m_bottom_edge_size_px(0),
	m_left_edge_size_px(0),
	m_right_edge_size_px(0)
{
	/** Nothing **/
}

GUIBackground::TextureData::TextureData(unsigned int edge_size_px)
	:m_top_edge_size_px(edge_size_px),
	m_bottom_edge_size_px(edge_size_px),
	m_left_edge_size_px(edge_size_px),
	m_right_edge_size_px(edge_size_px)
{
	/** Nothing **/
}

GUIBackground::TextureData::TextureData(unsigned int top_and_bottom_edge_size_px, unsigned int left_and_right_edge_size_px)
	:m_top_edge_size_px(top_and_bottom_edge_size_px),
	m_left_edge_size_px(left_and_right_edge_size_px),
	m_bottom_edge_size_px(top_and_bottom_edge_size_px),
	m_right_edge_size_px(left_and_right_edge_size_px)
{
	/** Nothing**/
}

GUIBackground::TextureData::TextureData(unsigned int top_edge_size_px, unsigned int left_edge_size_px, unsigned int bottom_edge_size_px, unsigned int right_edge_size_px)
	:m_top_edge_size_px(top_edge_size_px),
	m_left_edge_size_px(left_edge_size_px),
	m_bottom_edge_size_px(bottom_edge_size_px),
	m_right_edge_size_px(right_edge_size_px)
{
	/** Nothing **/
}


GUIBackground::GUIBackground(const TextureManager& texture_manager, const std::string& texture_id, const TextureData& texture_data)
	:m_texture(texture_manager.getTexture(texture_id)),
	m_texture_data(texture_data)
{
	/** Nothing **/
}

GUIBackground::GUIBackground(const GUIBackground& copy)
	:m_texture(copy.m_texture),
	m_texture_data(copy.m_texture_data)
{
	/** Nothing**/
}

#if 0
GUIBackground::GUIBackground(TextureManager& texture_manager,
	const std::string& texture_id,
	EdgeType edge_type,
	unsigned int edge_size_px,
	unsigned int width_px,
	unsigned int height_px)
{
	const sf::Texture& texture(texture_manager.getTexture(texture_id));
	sf::Sprite background;
	sf::Sprite top_edge_sprite, right_edge_sprite, bottom_edge_sprite, left_edge_sprite;
	sf::Sprite top_left_corner_sprite, top_right_corner_sprite, bottom_right_corner_sprite, bottom_left_corner_sprite;
	unsigned int vertical_elements_count(3), horizontal_element_count(2);
	unsigned int temp_x, temp_y;
	std::map<EdgeType, set_edge_function> set_edge_function_map;
	std::map<EdgeType, set_edge_function>::iterator it;

	set_edge_function_map[COPY] = &GUIBackground::setEdgeCopy;
	set_edge_function_map[SCALE] = &GUIBackground::setEdgeScale;

	temp_x = texture.getSize().x;
	temp_y = texture.getSize().y;
	vertical_elements_count = ((width_px + (temp_x >> 1)) / temp_x);
	horizontal_element_count = ((height_px + (temp_y >> 1)) / temp_y);

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

	m_renderer.create(vertical_elements_count * background.getTextureRect().width + 2 * edge_size_px, horizontal_element_count * background.getTextureRect().height + 2 * edge_size_px);
	m_renderer.clear(sf::Color::Blue);

	setBackground(background, vertical_elements_count, horizontal_element_count, edge_size_px);

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

	m_renderer.display();
	m_sprite.setTexture(m_renderer.getTexture());
}
#endif

void GUIBackground::setScreenPosition(unsigned int left_px, unsigned int top_px)
{
	int dx(0), dy(0);

	m_sprite.setPosition(left_px, top_px);

	//moveBy(dx, dy);
}

void GUIBackground::setDimensions(unsigned int width_px, unsigned int height_px)
{
	sf::Sprite background;
	sf::Sprite top_edge_sprite, right_edge_sprite, bottom_edge_sprite, left_edge_sprite;
	sf::Sprite top_left_corner_sprite, top_right_corner_sprite, bottom_right_corner_sprite, bottom_left_corner_sprite;
	unsigned int vertical_elements_count(1), horizontal_element_count(1);
	unsigned int temp_x, temp_y;

	temp_x = m_texture.getSize().x;
	temp_y = m_texture.getSize().y;
	/*vertical_elements_count = ((width_px + (temp_x >> 1)) / temp_x) + 1;
	horizontal_element_count = ((height_px + (temp_y >> 1)) / temp_y) + 1;*/

	vertical_elements_count = (width_px + m_texture_data.m_left_edge_size_px + m_texture_data.m_right_edge_size_px) / temp_x + 1;
	horizontal_element_count = (height_px + m_texture_data.m_top_edge_size_px + m_texture_data.m_bottom_edge_size_px) / temp_y + 1;

	background.setTexture(m_texture);
	background.setTextureRect(
		sf::IntRect(
			m_texture_data.m_left_edge_size_px,
			m_texture_data.m_top_edge_size_px,
			m_texture.getSize().x - (m_texture_data.m_left_edge_size_px + m_texture_data.m_right_edge_size_px),
			m_texture.getSize().y - (m_texture_data.m_top_edge_size_px + m_texture_data.m_bottom_edge_size_px)));

	/** Corners **/

	top_left_corner_sprite.setTexture(m_texture);
	top_left_corner_sprite.setTextureRect(
		sf::IntRect(
			0,
			0,
			m_texture_data.m_left_edge_size_px,
			m_texture_data.m_top_edge_size_px));
	top_right_corner_sprite.setTexture(m_texture);

	top_right_corner_sprite.setTextureRect(
		sf::IntRect(
			m_texture.getSize().x - m_texture_data.m_right_edge_size_px,
			0,
			m_texture_data.m_right_edge_size_px,
			m_texture_data.m_top_edge_size_px));

	bottom_right_corner_sprite.setTexture(m_texture);
	bottom_right_corner_sprite.setTextureRect(
		sf::IntRect(
			m_texture.getSize().x - m_texture_data.m_right_edge_size_px,
			m_texture.getSize().y - m_texture_data.m_bottom_edge_size_px,
			m_texture_data.m_right_edge_size_px,
			m_texture_data.m_bottom_edge_size_px));

	bottom_left_corner_sprite.setTexture(m_texture);
	bottom_left_corner_sprite.setTextureRect(
		sf::IntRect(
			0,
			m_texture.getSize().y - m_texture_data.m_bottom_edge_size_px,
			m_texture_data.m_left_edge_size_px,
			m_texture_data.m_bottom_edge_size_px));

	/** Edges **/

	top_edge_sprite.setTexture(m_texture);
	top_edge_sprite.setTextureRect(
		sf::IntRect(
			m_texture_data.m_left_edge_size_px,
			0,
			m_texture.getSize().x - (m_texture_data.m_left_edge_size_px + m_texture_data.m_right_edge_size_px),
			m_texture_data.m_top_edge_size_px));

	right_edge_sprite.setTexture(m_texture);
	right_edge_sprite.setTextureRect(
		sf::IntRect(
			m_texture.getSize().x - m_texture_data.m_right_edge_size_px,
			m_texture_data.m_top_edge_size_px,
			m_texture_data.m_right_edge_size_px,
			m_texture.getSize().y - (m_texture_data.m_top_edge_size_px + m_texture_data.m_bottom_edge_size_px)));

	bottom_edge_sprite.setTexture(m_texture);
	bottom_edge_sprite.setTextureRect(
		sf::IntRect(
			m_texture_data.m_left_edge_size_px,
			m_texture.getSize().y - m_texture_data.m_bottom_edge_size_px,
			m_texture.getSize().x - (m_texture_data.m_left_edge_size_px + m_texture_data.m_right_edge_size_px),
			m_texture_data.m_bottom_edge_size_px));

	left_edge_sprite.setTexture(m_texture);
	left_edge_sprite.setTextureRect(
		sf::IntRect(
			0,
			m_texture_data.m_top_edge_size_px,
			m_texture_data.m_left_edge_size_px,
			m_texture.getSize().y - (m_texture_data.m_top_edge_size_px + m_texture_data.m_bottom_edge_size_px)));

	m_renderer.create(
		vertical_elements_count * background.getTextureRect().width + m_texture_data.m_left_edge_size_px + m_texture_data.m_right_edge_size_px,
		horizontal_element_count * background.getTextureRect().height + m_texture_data.m_top_edge_size_px + m_texture_data.m_bottom_edge_size_px);

	m_renderer.clear(sf::Color::Blue);

	setBackground(background, vertical_elements_count, horizontal_element_count, m_texture_data);

	setCorners(top_left_corner_sprite,
		top_right_corner_sprite,
		bottom_right_corner_sprite,
		bottom_left_corner_sprite,
		horizontal_element_count,
		vertical_elements_count,
		sf::Vector2i(background.getTextureRect().width, background.getTextureRect().height));

	setEdge(top_edge_sprite,
		right_edge_sprite,
		bottom_edge_sprite,
		left_edge_sprite,
		horizontal_element_count,
		vertical_elements_count,
		sf::Vector2i(background.getTextureRect().width, background.getTextureRect().height));

	m_renderer.display();
	m_sprite.setTexture(m_renderer.getTexture());
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_renderer.getTexture().getSize().x, m_renderer.getTexture().getSize().y));
}

sf::IntRect GUIBackground::getUsableDimensions(void) const
{
	sf::IntRect l_ret(0, 0, 0, 0);

	l_ret.left = m_sprite.getGlobalBounds().left + m_texture_data.m_left_edge_size_px;
	l_ret.top = m_sprite.getGlobalBounds().top + m_texture_data.m_top_edge_size_px;
	l_ret.width = m_sprite.getGlobalBounds().width - m_texture_data.m_right_edge_size_px;
	l_ret.height = m_sprite.getGlobalBounds().height - m_texture_data.m_bottom_edge_size_px;

	return l_ret;
}

sf::Vector2u GUIBackground::getDimensions(void) const
{
	sf::Vector2u l_ret;

	l_ret.x = m_sprite.getTextureRect().width;
	l_ret.y = m_sprite.getTextureRect().height;

	return l_ret;
}

void GUIBackground::moveBy(int dx, int dy)
{
	m_sprite.move(dx, dy);
}

void GUIBackground::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

std::unique_ptr<IGUIBackground> GUIBackground::clone(void) const
{
	return std::unique_ptr<IGUIBackground>(new GUIBackground(*this));
}

void GUIBackground::setBackground(sf::Sprite& sprite,
	unsigned int x_sub_sprite_count,
	unsigned int y_sub_sprite_count,
	const TextureData& texture_data)
{
	unsigned int x, y;
	unsigned int sprite_width(0), sprite_height(0);

	sprite_width = sprite.getTextureRect().width;
	sprite_height = sprite.getTextureRect().height;

	for (x = 0; x < x_sub_sprite_count; x++)
	{
		for (y = 0; y < y_sub_sprite_count; y++)
		{
			sprite.setPosition((x) * sprite_width + texture_data.m_left_edge_size_px, (y) * sprite_height + texture_data.m_top_edge_size_px);
			m_renderer.draw(sprite);
		}
	}
}

void GUIBackground::setEdge(sf::Sprite& top_edge_sprite,
	sf::Sprite& right_edge_sprite,
	sf::Sprite& bottom_edge_sprite,
	sf::Sprite& left_edge_sprite,
	unsigned int horizontal_sub_lignes_count,
	unsigned int vertical_sub_lignes_count,
	sf::Vector2i background_sprite_size)
{
	unsigned int x, y;

	/** Top and bottom **/
	for (x = 0; x < vertical_sub_lignes_count; x++)
	{
		top_edge_sprite.setPosition(
			(x) * background_sprite_size.x + left_edge_sprite.getTextureRect().width,
			0.0f);
		bottom_edge_sprite.setPosition(
			(x) * background_sprite_size.x + left_edge_sprite.getTextureRect().width,
			horizontal_sub_lignes_count * background_sprite_size.y + top_edge_sprite.getTextureRect().height);

		m_renderer.draw(top_edge_sprite);
		m_renderer.draw(bottom_edge_sprite);
	}

	for (y = 0; y < horizontal_sub_lignes_count; y++)
	{
		left_edge_sprite.setPosition(
			0.0f,
			(y) * background_sprite_size.y + top_edge_sprite.getTextureRect().height);
		right_edge_sprite.setPosition(
			vertical_sub_lignes_count * background_sprite_size.x + left_edge_sprite.getTextureRect().width,
			(y) * background_sprite_size.y + top_edge_sprite.getTextureRect().height);
		m_renderer.draw(left_edge_sprite);
		m_renderer.draw(right_edge_sprite);
	}
}

/*void GUIBackground::setEdgeCopy(sf::Sprite& top_edge_sprite,
								sf::Sprite& right_edge_sprite,
								sf::Sprite& bottom_edge_sprite,
								sf::Sprite& left_edge_sprite,
								unsigned int horizontal_sub_lignes_count,
								unsigned int vertical_sub_lignes_count,
								sf::Vector2i background_sprite_size)
{
	unsigned int x, y;

	/** Top and bottom ** /
	for (x = 0; x < vertical_sub_lignes_count; x++)
	{
		top_edge_sprite.setPosition((x) * background_sprite_size.x + left_edge_sprite.getTextureRect().width,
			0.0f);
		bottom_edge_sprite.setPosition((x) * background_sprite_size.x + left_edge_sprite.getTextureRect().width,
			horizontal_sub_lignes_count * background_sprite_size.y + top_edge_sprite.getTextureRect().height);
		m_renderer.draw(top_edge_sprite);
		m_renderer.draw(bottom_edge_sprite);
	}

	for (y = 0; y < horizontal_sub_lignes_count; y++)
	{
		left_edge_sprite.setPosition(0.0f,
			(y) * background_sprite_size.y + top_edge_sprite.getTextureRect().height);
		right_edge_sprite.setPosition(vertical_sub_lignes_count * background_sprite_size.x + left_edge_sprite.getTextureRect().width,
			(y) * background_sprite_size.y + top_edge_sprite.getTextureRect().height);
		m_renderer.draw(left_edge_sprite);
		m_renderer.draw(right_edge_sprite);
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

	m_renderer.draw(top_edge_sprite);
	m_renderer.draw(left_edge_sprite);
	m_renderer.draw(bottom_edge_sprite);
	m_renderer.draw(right_edge_sprite);
}*/

void GUIBackground::setCorners(	sf::Sprite& top_left_corner_sprite,
								sf::Sprite& top_right_corner_sprite,
								sf::Sprite& bottom_right_corner_sprite,
								sf::Sprite& bottom_left_corner_sprite,
								unsigned int horizontal_sub_elements_count,
								unsigned int vertical_sub_element_count,
								sf::Vector2i background_sprite_size)
{
	unsigned int x_offset_px(top_left_corner_sprite.getTextureRect().width);
	unsigned int y_offset_px(top_left_corner_sprite.getTextureRect().height);

	top_left_corner_sprite.setPosition(0, 0);
	top_right_corner_sprite.setPosition(vertical_sub_element_count * background_sprite_size.x + x_offset_px, 0);
	bottom_right_corner_sprite.setPosition(vertical_sub_element_count * background_sprite_size.x + x_offset_px, horizontal_sub_elements_count * background_sprite_size.y + y_offset_px);
	bottom_left_corner_sprite.setPosition(0, horizontal_sub_elements_count * background_sprite_size.y + y_offset_px);

	m_renderer.draw(top_left_corner_sprite);
	m_renderer.draw(top_right_corner_sprite);
	m_renderer.draw(bottom_left_corner_sprite);
	m_renderer.draw(bottom_right_corner_sprite);
}
