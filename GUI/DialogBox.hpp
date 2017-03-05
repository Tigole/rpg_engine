#ifndef _DIALOG_BOX_HPP
#define _DIALOG_BOX_HPP 1

#include <SFML/Graphics.hpp>

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
	sf::IntRect getInsideDimensions(void) const;
protected:
	std::vector<sf::Drawable*> m_drawable;
private:
	std::unique_ptr<IGUIBackground> m_background;
	bool m_hide_flag;
};

class TextDialogBox : public BasicDialogBox
{
public:
	struct TextData
	{
		TextData(sf::Font& font);
		TextData(sf::Font& font, unsigned int char_size_px);
		TextData(sf::Font& font, sf::Color color);
		TextData(sf::Font& font, sf::Color color, unsigned int char_size_px);

		sf::Font& m_font;
		sf::Color m_color;
		unsigned int m_char_size_px;
	};
	TextDialogBox();
	TextDialogBox(std::unique_ptr<IGUIBackground>& background, const TextData& text_data);
	TextDialogBox(std::unique_ptr<IGUIBackground>& background, const TextData& text_data, unsigned int left_px, unsigned int top_px);
	TextDialogBox(std::unique_ptr<IGUIBackground>& background, const TextData& text_data, unsigned int left_px, unsigned int top_px, const std::string& text);

	virtual void setText(const std::string& text);
	virtual void setText(const std::vector<std::string>& text);

protected:

	void initialize(const TextData& text_data);

	sf::Text m_text;
	sf::Font m_font;
};


#endif // !_DIALOG_BOX_HPP
