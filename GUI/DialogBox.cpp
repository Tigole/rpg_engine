#include "DialogBox.hpp"
#include "TextureManager.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <string>

#include <iostream>

IDialogBox::~IDialogBox()
{
	/** Nothing **/
}

/*BasicDialogBox::BasicDialogBox(int top_px, int left_px, unsigned int width_px, unsigned int height_px)
	: m_hide_flag(false),
	m_drawable()
{
	/** Nothing ** /
}*/

BasicDialogBox::BasicDialogBox()
	: m_drawable(),
	m_background(),
	m_hide_flag(true)
{
	/** Nothing **/
}

BasicDialogBox::BasicDialogBox(std::unique_ptr<IGUIBackground>& background)
	: m_drawable(),
	m_background(nullptr),
	m_hide_flag(true)
{
	setBackground(background);
}
BasicDialogBox::BasicDialogBox(std::unique_ptr<IGUIBackground>& background, unsigned int left_px, unsigned int top_px)
	: m_drawable(),
	m_background(nullptr),
	m_hide_flag(false)
{
	setBackground(background);
	setScreenPosition(left_px, top_px);
}

BasicDialogBox::BasicDialogBox(std::unique_ptr<IGUIBackground>& background, unsigned int left_px, unsigned int top_px, unsigned int width_px, unsigned int height_px)
	: m_drawable(),
	m_background(nullptr),
	m_hide_flag(false)
{
	setBackground(background);
	setScreenPosition(left_px, top_px);
	setDimensions(width_px, height_px);
}

void BasicDialogBox::setBackground(std::unique_ptr<IGUIBackground>& new_background)
{
	m_background.reset(new_background.release());
	m_hide_flag = m_hide_flag || (m_background == nullptr);
}

void BasicDialogBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (m_hide_flag == false)
	{
		//states.blendMode = sf::BlendMode(sf::BlendMode::SrcColor, sf::BlendMode::DstColor);
		target.draw(*m_background, states);
		for (auto& a : m_drawable)
			target.draw(*a, states);
	}
	else
	{
		/** Nothing **/
	}
}

void BasicDialogBox::hide(bool hide)
{
	m_hide_flag = hide || (m_background == nullptr);
}

void BasicDialogBox::setScreenPosition(unsigned int left_px, unsigned int top_px)
{
	m_background->setScreenPosition(top_px, left_px);
}

void BasicDialogBox::setDimensions(unsigned int width_px, unsigned int height_px)
{
	m_background->setDimensions(width_px, height_px);
}

sf::IntRect BasicDialogBox::getInsideDimensions(void) const
{
	sf::IntRect l_ret(0, 0, 0, 0);

	if (m_background != nullptr)
		l_ret = m_background->getUsableDimensions();

	return l_ret;
}



TextDialogBox::TextData::TextData(sf::Font& font)
	:m_font(font),
	m_color(sf::Color(sf::Color::White)),
	m_char_size_px(10)
{
	/** Nothing **/
}

TextDialogBox::TextData::TextData(sf::Font& font, unsigned int char_size_px)
	:m_font(font),
	m_color(sf::Color(sf::Color::White)),
	m_char_size_px(char_size_px)
{
	/** Nothing **/
}

TextDialogBox::TextData::TextData(sf::Font& font, sf::Color color)
	:m_font(font),
	m_color(color),
	m_char_size_px(10)
{
	/** Nothing **/
}

TextDialogBox::TextData::TextData(sf::Font& font, sf::Color color, unsigned int char_size_px)
	:m_font(font),
	m_color(color),
	m_char_size_px(char_size_px)
{
	/** Nothing **/
}

TextDialogBox::TextDialogBox()
{
	m_drawable.push_back(&m_text);
}

TextDialogBox::TextDialogBox(std::unique_ptr<IGUIBackground>& background, const TextData& text_data)
	: BasicDialogBox(background)
{
	initialize(text_data);
}

TextDialogBox::TextDialogBox(std::unique_ptr<IGUIBackground>& background, const TextData& text_data, unsigned int left_px, unsigned int top_px)
	: BasicDialogBox(background, left_px, top_px)
{
	initialize(text_data);
	setScreenPosition(left_px, top_px);
}

TextDialogBox::TextDialogBox(std::unique_ptr<IGUIBackground>& background, const TextData& text_data, unsigned int left_px, unsigned int top_px, const std::string& text)
	: BasicDialogBox(background, left_px, top_px)
{
	initialize(text_data);
	setScreenPosition(left_px, top_px);
	setText(text);
}

void TextDialogBox::initialize(const TextData& text_data)
{
	m_drawable.push_back(&m_text);
	m_font = text_data.m_font;
	m_text.setFont(m_font);
	m_text.setCharacterSize(text_data.m_char_size_px);
	m_text.setColor(text_data.m_color);
}

void TextDialogBox::setText(const std::string& text)
{
	m_text.setString(text);
	setDimensions(m_text.getLocalBounds().width, m_text.getLocalBounds().height);
	m_text.setPosition(getInsideDimensions().left, getInsideDimensions().top);
}

void TextDialogBox::setText(const std::vector<std::string>& text)
{
	//
}
