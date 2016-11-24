#ifndef _GUI_HPP
#define _GUI_HPP 1

#include <SFML\Graphics.hpp>
#include <vector>

#include "Miscellaneous.hpp"

class TextureManager;

class IGUIBackground : public sf::Drawable, public misc::Clonable<IGUIBackground>
{
public:
	virtual ~IGUIBackground();

	virtual void setScreenPosition(unsigned int left_px, unsigned int top_px) = 0;
	virtual void moveBy(int dx, int dy) = 0;
	virtual void setDimensions(unsigned int width_px, unsigned int height_px) = 0;
	virtual sf::Vector2u getUsableDimensions(void) const = 0;
	virtual sf::Vector2u getDimensions(void) const = 0;
};

class GUIBackground : public IGUIBackground
{
public:
	enum EdgeType
	{
		COPY,
		SCALE
	};
	struct TextureData
	{
		TextureData();
		TextureData(unsigned int edge_size_px);
		TextureData(unsigned int top_and_bottom_edge_size_px, unsigned int left_and_right_edge_size_px);
		TextureData(unsigned int top_edge_size_px, unsigned int left_edge_size_px, unsigned int bottom_edge_size_px, unsigned int right_edge_size_px);

		unsigned int m_top_edge_size_px;
		unsigned int m_left_edge_size_px;
		unsigned int m_bottom_edge_size_px;
		unsigned int m_right_edge_size_px;
	};
	GUIBackground(const TextureManager& texture_manager, const std::string& texture_id, const TextureData& texture_data);
	GUIBackground(const GUIBackground& copy);

	virtual void setScreenPosition(unsigned int left_px, unsigned int top_px);
	virtual void moveBy(int dx, int dy);
	virtual void setDimensions(unsigned int width_px, unsigned int height_px);
	sf::Vector2u getUsableDimensions(void) const;
	virtual sf::Vector2u getDimensions(void) const;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	std::unique_ptr<IGUIBackground> clone(void) const;

protected:
	virtual void setBackground(sf::Sprite& sprite,
		unsigned int x_sub_sprite_count,
		unsigned int y_sub_sprite_count,
		const TextureData& texture_data);
	virtual void setEdge(sf::Sprite& top_edge_sprite,
		sf::Sprite& right_edge_sprite,
		sf::Sprite& bottom_edge_sprite,
		sf::Sprite& left_edge_sprite,
		unsigned int horizontal_sub_lignes_count,
		unsigned int vertical_sub_lignes_count,
		sf::Vector2i background_sprite_size);
	/*virtual void setEdgeCopy(sf::Sprite& top_edge_sprite,
		sf::Sprite& right_edge_sprite, 
		sf::Sprite& bottom_edge_sprite, 
		sf::Sprite& left_edge_sprite, 
		unsigned int horizontal_sub_lignes_count, 
		unsigned int vertical_sub_lignes_count, 
		sf::Vector2i background_sprite_size);*/
	/*virtual void setEdgeScale(sf::Sprite& top_edge_sprite,
		sf::Sprite& right_edge_sprite,
		sf::Sprite& bottom_edge_sprite,
		sf::Sprite& left_edge_sprite,
		unsigned int horizontal_sub_lignes_count,
		unsigned int vertical_sub_lignes_count,
		sf::Vector2i background_sprite_size);*/
	virtual void setCorners(sf::Sprite& top_left_corner_sprite,
		sf::Sprite& top_right_corner_sprite,
		sf::Sprite& bottom_right_corner_sprite,
		sf::Sprite& bottom_left_corner_sprite,
		unsigned int horizontal_sub_lignes_count, 
		unsigned int vertical_sub_lignes_count, 
		sf::Vector2i background_sprite_size);

	const sf::Texture& m_texture;
	TextureData m_texture_data;
	sf::Sprite m_sprite;
	sf::RenderTexture m_renderer;
	sf::Transformable m_transformable;
};

#endif // !_GUI_HPP