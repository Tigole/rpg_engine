#ifndef _GUI_HPP
#define _GUI_HPP 1

#include <SFML\Graphics.hpp>

#include <vector>

class TextureManager;

class IGUIBackground : public sf::Drawable
{
public:
	virtual ~IGUIBackground();

	virtual void setScreenPosition(int top_px, int left_px) = 0;
	virtual void moveBy(int dx, int dy) = 0;
	//virtual void setDimensions(int width_px, int height_px) = 0;
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
	GUIBackground();
	GUIBackground(TextureManager& texture_manager, 
		const std::string& texture_id,
		EdgeType edge_type,
		unsigned int edge_size_px, 
		unsigned int left_px, 
		unsigned int top_px, 
		unsigned int width_px, 
		unsigned int height_px);

	virtual void setScreenPosition(int left_px, int top_px);
	virtual void moveBy(int dx, int dy);
	//virtual void setDimensions(int width_px, int height_px);
	sf::Vector2u getDimensions(void) const;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

protected:
	typedef void(GUIBackground::*set_edge_function)(sf::Sprite& top_edge_sprite,
		sf::Sprite& right_edge_sprite,
		sf::Sprite& bottom_edge_sprite,
		sf::Sprite& left_edge_sprite,
		unsigned int horizontal_sub_lignes_count,
		unsigned int vertical_sub_lignes_count,
		sf::Vector2i background_sprite_size);
	void setBackground(sf::Sprite& sprite, unsigned int edge_size_px);
	void setEdgeCopy(sf::Sprite& top_edge_sprite, 
		sf::Sprite& right_edge_sprite, 
		sf::Sprite& bottom_edge_sprite, 
		sf::Sprite& left_edge_sprite, 
		unsigned int horizontal_sub_lignes_count, 
		unsigned int vertical_sub_lignes_count, 
		sf::Vector2i background_sprite_size);
	void setEdgeScale(sf::Sprite& top_edge_sprite,
		sf::Sprite& right_edge_sprite,
		sf::Sprite& bottom_edge_sprite,
		sf::Sprite& left_edge_sprite,
		unsigned int horizontal_sub_lignes_count,
		unsigned int vertical_sub_lignes_count,
		sf::Vector2i background_sprite_size);
	void setCorners(sf::Sprite& top_left_corner_sprite,
		sf::Sprite& top_right_corner_sprite,
		sf::Sprite& bottom_right_corner_sprite,
		sf::Sprite& bottom_left_corner_sprite,
		unsigned int horizontal_sub_lignes_count, 
		unsigned int vertical_sub_lignes_count, 
		sf::Vector2i background_sprite_size);
	void resize(unsigned int new_size);
	void resize(unsigned int x_size, unsigned int y_size);
	std::vector<std::vector<sf::Sprite>> m_background;
};

#endif // !_GUI_HPP