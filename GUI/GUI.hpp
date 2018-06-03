#ifndef _GUI_HPP
#define _GUI_HPP 1

#include <SFML/Graphics.hpp>
#include <vector>

#include "Miscellaneous.hpp"

class TextureManager;
#if 0
class IGUIBackground : public sf::Drawable, public misc::Clonable<IGUIBackground>
{
public:
	virtual ~IGUIBackground();

	virtual void mt_Set_Screen_Position(unsigned int left_px, unsigned int top_px) = 0;
	virtual void mt_Move_By(int dx, int dy) = 0;
	virtual void mt_Set_Dimensions(unsigned int width_px, unsigned int height_px) = 0;
	virtual sf::IntRect mt_Get_Usable_Dimensions(void) const = 0;
	virtual sf::Vector2u mt_Get_Dimensions(void) const = 0;
};

class GUIBackground : public IGUIBackground
{
public:
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
	GUIBackground(TextureManager& texture_manager, const std::string& texture_id, const TextureData& texture_data);
	GUIBackground(const GUIBackground& copy);

	virtual void mt_Set_Screen_Position(unsigned int left_px, unsigned int top_px);
	virtual void mt_Move_By(int dx, int dy);
	virtual void mt_Set_Dimensions(unsigned int width_px, unsigned int height_px);
	sf::IntRect mt_Get_Usable_Dimensions(void) const;
	virtual sf::Vector2u mt_Get_Dimensions(void) const;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	std::unique_ptr<IGUIBackground> mt_Clone(void) const;

protected:
	virtual void mt_Set_Background(sf::Sprite& sprite,
		unsigned int x_sub_sprite_count,
		unsigned int y_sub_sprite_count,
		const TextureData& texture_data);
	virtual void mt_Set_Edge(sf::Sprite& top_edge_sprite,
		sf::Sprite& right_edge_sprite,
		sf::Sprite& bottom_edge_sprite,
		sf::Sprite& left_edge_sprite,
		unsigned int horizontal_sub_lignes_count,
		unsigned int vertical_sub_lignes_count,
		sf::Vector2i background_sprite_size);
	virtual void mt_Set_Corners(sf::Sprite& top_left_corner_sprite,
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
	sf::IntRect m_usable_dimension;
};
#endif
#endif // !_GUI_HPP
