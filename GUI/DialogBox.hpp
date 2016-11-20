#ifndef _DIALOG_BOX_HPP
#define _DIALOG_BOX_HPP 1

#include <SFML\Graphics.hpp>

#include "GUI.hpp"

class TextureManager;

class IDialogBox : public sf::Drawable
{
public:
	virtual ~IDialogBox();

	virtual void hide(bool hide) = 0;
	virtual void setScreenPosition(int top_px, int left_px) = 0;
	virtual void setDimensions(int width_px, int height_px) = 0;
};

class BasicDialogBox : public IDialogBox
{
public:
	BasicDialogBox(int top_px, int left_px, unsigned int width_px, unsigned int height_px);
	BasicDialogBox(TextureManager& texture_manager);
	BasicDialogBox(TextureManager& texture_manager, const std::string& texture_id, unsigned int edge_size_px, unsigned int top_px, unsigned int left_px, unsigned int width_px, unsigned int height_px);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual void hide(bool hide);

	virtual void setEdgeSize(int edge_size_px);
	virtual void setScreenPosition(int top_px, int left_px);
	virtual void setDimensions(int width_px, int height_px);
protected:
	sf::Sprite m_background_sprite;
	sf::Texture m_background_texture;
	GUIBackground m_background;
	bool m_hide_flag;
};

#endif // !_DIALOG_BOX_HPP