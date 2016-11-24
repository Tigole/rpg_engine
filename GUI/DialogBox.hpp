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
	virtual void setScreenPosition(unsigned int top_px, unsigned int left_px) = 0;
	virtual void setDimensions(unsigned int width_px, unsigned int height_px) = 0;
};

class BasicDialogBox : public IDialogBox
{
public:
	BasicDialogBox();
	BasicDialogBox(std::unique_ptr<IGUIBackground>& background);
	BasicDialogBox(std::unique_ptr<IGUIBackground>& background, unsigned int left_px, unsigned int top_px);
	BasicDialogBox(std::unique_ptr<IGUIBackground>& background, unsigned int left_px, unsigned int top_px, unsigned int width_px, unsigned int height_px);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	
	virtual void hide(bool hide);
	virtual void setScreenPosition(unsigned int left_px, unsigned int top_px);
	virtual void setDimensions(unsigned int width_px, unsigned int height_px);
	void setBackground(std::unique_ptr<IGUIBackground>& new_background);
	sf::Vector2u getInsideDimensions(void) const;
protected:
	std::vector<sf::Drawable*> m_drawable;
private:
	std::unique_ptr<IGUIBackground> m_background;
	bool m_hide_flag;
};

#endif // !_DIALOG_BOX_HPP