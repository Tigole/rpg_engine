#include "DialogBox.hpp"
#include "TextureManager.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <string>


IDialogBox::~IDialogBox()
{
	/** Nothing **/
}

BasicDialogBox::BasicDialogBox(int top_px, int left_px, unsigned int width_px, unsigned int height_px)
	: m_hide_flag(false)
{
	sf::Texture texture;
	sf::Image image, dest_image;

	image.create(width_px, height_px, sf::Color(219, 23, 2));
	m_background_texture.create(width_px, height_px);
	m_background_texture.update(image);

	m_background_texture.loadFromFile("C:/Users/Janniere Sylvain/Documents/GitHub/rpg_engine/Resources/Texture/dlg.png");



	//image.loadFromFile("C:/Users/Janniere Sylvain/Documents/GitHub/rpg_engine/Resources/Texture/dlg.png");
	//texture


	m_background_sprite.setTexture(m_background_texture);
	m_background_sprite.setPosition((float)top_px, (float)left_px);
	// dlg_top_left
}

BasicDialogBox::BasicDialogBox(TextureManager& texture_manager)
{
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RenderTexture renderer;

	texture = texture_manager.getTexture("dlg");
	sprite.setTextureRect(sf::IntRect(0, 0, 11, 11));
	renderer.draw(sprite);

	m_background_texture = renderer.getTexture();
	m_background_sprite.setTexture(m_background_texture);
}

BasicDialogBox::BasicDialogBox(TextureManager& texture_manager, const std::string& resource_file, unsigned int edge_size_px, unsigned int top_px, unsigned int left_px, unsigned int width_px, unsigned int height_px)
{
	sf::Texture& texture(texture_manager.getTexture(resource_file));
	sf::Sprite background, corner, edge;
	
	edge.setTexture(texture);
	edge.setTextureRect(sf::IntRect(edge_size_px, 0, edge_size_px, edge_size_px));

	corner.setTexture(texture);
	corner.setTextureRect(sf::IntRect(0, edge_size_px, edge_size_px, edge_size_px));

	background.setTexture(texture);
	background.setTextureRect(sf::IntRect(edge_size_px, edge_size_px, texture.getSize().x - edge_size_px, texture.getSize().y - edge_size_px));
}

void BasicDialogBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (m_hide_flag == false)
	{
		//states.blendMode = sf::BlendMode(sf::BlendMode::SrcColor, sf::BlendMode::DstColor);
		target.draw(m_background_sprite, states);
	}
	else
	{
		/** Nothing **/
	}
}

void BasicDialogBox::hide(bool hide)
{
	m_hide_flag = hide;
}

void BasicDialogBox::setEdgeSize(int edge_size_px)
{
	//
}

void BasicDialogBox::setScreenPosition(int top_px, int left_px)
{
	m_background_sprite.setPosition((float)top_px, (float)left_px);
}

void BasicDialogBox::setDimensions(int width_px, int height_px)
{
	sf::Vector2f targetSize((float)width_px, (float)height_px);

	m_background_sprite.setScale(
		targetSize.x / m_background_sprite.getLocalBounds().width,
		targetSize.y / m_background_sprite.getLocalBounds().height);
}
