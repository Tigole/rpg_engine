#include "DialogBox.hpp"
#include "TextureManager.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <string>

#include <iostream>
#if 0
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
	mt_Set_Background(background);
}
BasicDialogBox::BasicDialogBox(std::unique_ptr<IGUIBackground>& background, unsigned int left_px, unsigned int top_px)
	: m_drawable(),
	m_background(nullptr),
	m_hide_flag(false)
{
	mt_Set_Background(background);
	mt_Set_Screen_Position(left_px, top_px);
}

BasicDialogBox::BasicDialogBox(std::unique_ptr<IGUIBackground>& background, unsigned int left_px, unsigned int top_px, unsigned int width_px, unsigned int height_px)
	: m_drawable(),
	m_background(nullptr),
	m_hide_flag(false)
{
	mt_Set_Background(background);
	mt_Set_Screen_Position(left_px, top_px);
	mt_Set_Dimensions(width_px, height_px);
}

void BasicDialogBox::mt_Set_Background(std::unique_ptr<IGUIBackground>& new_background)
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

void BasicDialogBox::mt_Hide(bool hide)
{
	m_hide_flag = hide || (m_background == nullptr);
}

void BasicDialogBox::mt_Set_Screen_Position(unsigned int left_px, unsigned int top_px)
{
	m_background->mt_Set_Screen_Position(top_px, left_px);
}

void BasicDialogBox::mt_Set_Dimensions(unsigned int width_px, unsigned int height_px)
{
	m_background->mt_Set_Dimensions(width_px, height_px);
}

sf::IntRect BasicDialogBox::mt_Get_Inside_Dimensions(void) const
{
	sf::IntRect l_ret(0, 0, 0, 0);

	if (m_background != nullptr)
		l_ret = m_background->mt_Get_Usable_Dimensions();

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
	mt_Initialize(text_data);
}

TextDialogBox::TextDialogBox(std::unique_ptr<IGUIBackground>& background, const TextData& text_data, unsigned int left_px, unsigned int top_px)
	: BasicDialogBox(background, left_px, top_px)
{
	mt_Initialize(text_data);
	mt_Set_Screen_Position(left_px, top_px);
}

TextDialogBox::TextDialogBox(std::unique_ptr<IGUIBackground>& background, const TextData& text_data, unsigned int left_px, unsigned int top_px, const std::string& text)
	: BasicDialogBox(background, left_px, top_px)
{
	mt_Initialize(text_data);
	mt_Set_Screen_Position(left_px, top_px);
	mt_Set_Text(text);
}

void TextDialogBox::mt_Initialize(const TextData& text_data)
{
	m_drawable.push_back(&m_text);
	m_font = text_data.m_font;
	m_text.setFont(m_font);
	m_text.setCharacterSize(text_data.m_char_size_px);
	m_text.setColor(text_data.m_color);
}

void TextDialogBox::mt_Set_Text(const std::string& text)
{
	m_text.setString(text);
	mt_Set_Dimensions(m_text.getLocalBounds().width, m_text.getLocalBounds().height);
	m_text.setPosition(mt_Get_Inside_Dimensions().left, mt_Get_Inside_Dimensions().top);
}

void TextDialogBox::mt_Set_Text(const std::vector<std::string>& text)
{
	//
}
#endif