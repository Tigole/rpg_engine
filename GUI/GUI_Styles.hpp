#ifndef _GUI_STYLE_HPP
#define _GUI_STYLE_HPP 1

#include <SFML/Graphics.hpp>

enum class GUI_Style_TextVAlign
{
	Top,
	Mid,
	Bottom
};

enum class GUI_Style_TextHAlign
{
	Left,
	Center,
	Right
};

struct GUI_Style
{
	struct Background
	{
		sf::Color m_background_color;
		sf::Color m_outline_color;
		float m_outline_thickness;
	};

	struct Text
	{
		GUI_Style_TextVAlign m_v_align;
		GUI_Style_TextHAlign m_h_align;
		sf::Vector2u m_margin;
		std::string m_font_id;
		sf::Color m_color;
		unsigned int m_size;
	};

	Background m_background;
	Text m_text;
};

struct GUI_Visual
{
	sf::Text m_text;
	sf::RectangleShape m_background;
};


std::string fn_GUIStyleTextHAlign_ToString(const GUI_Style_TextHAlign& align);
GUI_Style_TextHAlign fn_GUIStyleTextHAlign_ToEnum(const std::string& align);
std::string fn_GUIStyleTextVAlign_ToString(const GUI_Style_TextVAlign& align);
GUI_Style_TextVAlign fn_GUIStyleTextVAlign_ToEnum(const std::string& align);


#endif // !_GUI_STYLE_HPP