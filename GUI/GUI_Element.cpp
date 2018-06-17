#include "GUI_Element.hpp"
#include "Environment.hpp"


std::string fn_GUIElementState_ToString(const GUI_Element_State& state)
{
	std::string l_ret("");
	std::unordered_map<GUI_Element_State, std::string> l_map;
	std::unordered_map<GUI_Element_State, std::string>::iterator l_it;

	l_map[GUI_Element_State::Neutral] = "Neutral";
	l_map[GUI_Element_State::Clicked] = "Clicked";
	l_map[GUI_Element_State::Focused] = "Focused";

	l_it = l_map.find(state);
	if (l_it != l_map.end())
	{
		l_ret = l_it->second;
	}

	return l_ret;
}

GUI_Element_State fn_GUIElementState_ToEnum(const std::string& state)
{
	GUI_Element_State l_ret((GUI_Element_State)0xff);
	std::unordered_map<std::string, GUI_Element_State> l_map;
	std::unordered_map<std::string, GUI_Element_State>::iterator l_it;

	l_map["Neutral"] = GUI_Element_State::Neutral;
	l_map["Clicked"] = GUI_Element_State::Clicked;
	l_map["Focused"] = GUI_Element_State::Focused;

	l_it = l_map.find(state);
	if (l_it != l_map.end())
	{
		l_ret = l_it->second;
	}

	return l_ret;
}

std::string fn_GUIStyleTextHAlign_ToString(const GUI_Style_TextHAlign& align)
{
	std::map<GUI_Style_TextHAlign, std::string> l_map;
	auto l_it = l_map.end();

	std::string l_ret;

	l_map[GUI_Style_TextHAlign::Left] = "Left";
	l_map[GUI_Style_TextHAlign::Center] = "Center";
	l_map[GUI_Style_TextHAlign::Right] = "Right";

	l_it = l_map.find(align);
	if (l_it != l_map.end())
	{
		l_ret = l_it->second;
	}

	return l_ret;
}

GUI_Style_TextHAlign fn_GUIStyleTextHAlign_ToEnum(const std::string& align)
{
	std::map<std::string, GUI_Style_TextHAlign> l_map;
	auto l_it = l_map.end();

	GUI_Style_TextHAlign l_ret(GUI_Style_TextHAlign::Left);

	l_map["left"] = GUI_Style_TextHAlign::Left;
	l_map["Left"] = GUI_Style_TextHAlign::Left;
	l_map["center"] = GUI_Style_TextHAlign::Center;
	l_map["Center"] = GUI_Style_TextHAlign::Center;
	l_map["right"] = GUI_Style_TextHAlign::Right;
	l_map["Right"] = GUI_Style_TextHAlign::Right;

	l_it = l_map.find(align);
	if (l_it != l_map.end())
	{
		l_ret = l_it->second;
	}

	return l_ret;
}

std::string fn_GUIStyleTextVAlign_ToString(const GUI_Style_TextVAlign& align)
{
	std::map<GUI_Style_TextVAlign, std::string> l_map;
	auto l_it = l_map.end();

	std::string l_ret;

	l_map[GUI_Style_TextVAlign::Top] = "Top";
	l_map[GUI_Style_TextVAlign::Mid] = "Mid";
	l_map[GUI_Style_TextVAlign::Bottom] = "Bottom";

	l_it = l_map.find(align);
	if (l_it != l_map.end())
	{
		l_ret = l_it->second;
	}

	return l_ret;
}

GUI_Style_TextVAlign fn_GUIStyleTextVAlign_ToEnum(const std::string& align)
{
	std::map<std::string, GUI_Style_TextVAlign> l_map;
	auto l_it = l_map.end();

	GUI_Style_TextVAlign l_ret(GUI_Style_TextVAlign::Mid);

	l_map["top"] = GUI_Style_TextVAlign::Top;
	l_map["Top"] = GUI_Style_TextVAlign::Top;
	l_map["mid"] = GUI_Style_TextVAlign::Mid;
	l_map["Mid"] = GUI_Style_TextVAlign::Mid;
	l_map["bottom"] = GUI_Style_TextVAlign::Bottom;
	l_map["Bottom"] = GUI_Style_TextVAlign::Bottom;

	l_it = l_map.find(align);
	if (l_it != l_map.end())
	{
		l_ret = l_it->second;
	}

	return l_ret;
}


GUI_Element::GUI_Element(const std::string& id, GUI_Element* owner)
	:m_id(id), m_owner(owner), m_current_state(static_cast<GUI_Element_State>(0xff))
{}

void GUI_Element::mt_Set_Allocation(const sf::FloatRect& rect)
{
	m_allocation = rect;
}

void GUI_Element::mt_Set_Environment(Environment* env)
{
	m_environment = env;
}

void GUI_Element::mt_Set_Style(const GUI_Element_State& state, const GUI_Style& style)
{
	m_styles.emplace(std::make_pair(state, style));
}

void GUI_Element::mt_Set_State(const GUI_Element_State& state)
{
	if (state != m_current_state)
	{
		m_current_state = state;
		auto l_style = m_styles.find(m_current_state);

		if (l_style != m_styles.end())
		{
			mt_Apply_Style(l_style->second);
		}
	}
}

GUI_Element_State GUI_Element::mt_Get_State(void) const
{
	return m_current_state;
}

void GUI_Element::mt_On_Click(const sf::Vector2f& mousePos)
{
	mt_Set_State(GUI_Element_State::Clicked);
}

void GUI_Element::mt_On_Release(const sf::Vector2f& mousePos)
{
	if (mt_Is_Inside(mousePos) == true)
	{
		mt_Set_State(GUI_Element_State::Focused);
	}
	else
	{
		mt_Set_State(GUI_Element_State::Neutral);
	}
}

void GUI_Element::mt_On_Hover(const sf::Vector2f& mousePos)
{
	if (m_current_state != GUI_Element_State::Clicked)
	{
		bool l_is_inside(mt_Is_Inside(mousePos));
		
		if (l_is_inside == true)
		{
			mt_Set_State(GUI_Element_State::Focused);
		}
		else
		{
			mt_Set_State(GUI_Element_State::Neutral);
		}
	}
}

sf::FloatRect GUI_Element::mt_Get_Screen_Space(void) const
{
	return m_allocation;
}

sf::Vector2f GUI_Element::mt_Get_Required_Space(void) const
{
	sf::Vector2f l_ret(0, 0);

	sf::Text l_text(m_visual.m_text);
	l_text.setOrigin(0.0f, 0.0f);

	for (auto& l_style : m_styles)
	{
		sf::FloatRect l_rect;

		l_text.setFont(*(m_environment->m_font_manager.mt_Get_Resource(l_style.second.m_text.m_font_id)));
		l_text.setCharacterSize(l_style.second.m_text.m_size);

		l_rect = l_text.getLocalBounds();

		if (l_ret.x < l_rect.width)
		{
			l_ret.x = l_rect.width;
		}

		if (l_ret.y < l_rect.height)
		{
			l_ret.y = l_rect.height;
		}
	}

	return l_ret;
}

bool GUI_Element::mt_Is_Inside(const sf::Vector2f& position)
{
	return mt_Get_Screen_Space().contains(position);
}

const std::string& GUI_Element::mt_Get_Id(void) const
{
	return m_id;
}

sf::Vector2f GUI_Element::mt_Get_Screen_Position(void) const
{
	sf::Vector2f l_ret(m_allocation.left, m_allocation.top);

	if (m_owner != nullptr)
	{
		l_ret += m_owner->mt_Get_Screen_Position();
	}

	return l_ret;
}

void GUI_Element::mt_Set_Text(const std::string& text)
{
	m_visual.m_text.setString(text);
	mt_Redraw();
}

void GUI_Element::mt_Redraw(void)
{
	auto& l_style = m_styles.find(m_current_state);

	if (l_style != m_styles.end())
	{
		mt_Apply_Style(l_style->second);
	}
}

void GUI_Element::mt_Apply_Style(const GUI_Style& style)
{
	mt_Apply_Style_Background(style);
	mt_Apply_Style_Text(style);
}

void GUI_Element::mt_Apply_Style_Text(const GUI_Style& style)
{
	sf::FloatRect l_text_position;
	sf::Vector2f l_origin, l_position;
	sf::Font* l_font((m_environment->m_font_manager.mt_Get_Resource(style.m_text.m_font_id)));

	if (l_font != nullptr)
	{
		m_visual.m_text.setFont(*l_font);
	}

	m_visual.m_text.setColor(style.m_text.m_color);
	m_visual.m_text.setCharacterSize(style.m_text.m_size);

	l_text_position = m_visual.m_text.getGlobalBounds();

	if (style.m_text.m_h_align == GUI_Style_TextHAlign::Center)
	{
		l_position.x = m_allocation.left + (m_allocation.width / 2 - l_text_position.width / 2);
	}
	else
	{
		l_position.x = m_allocation.left;
	}

	if (style.m_text.m_v_align == GUI_Style_TextVAlign::Mid)
	{
		l_position.y = m_allocation.top + (m_allocation.height / 2 - l_text_position.height / 2);
	}
	else
	{
		l_position.y = m_allocation.top;
	}

	m_visual.m_text.setPosition(l_position.x + style.m_text.m_margin.x, l_position.y + style.m_text.m_margin.y);
}

void GUI_Element::mt_Apply_Style_Background(const GUI_Style& style)
{
	m_visual.m_background.setPosition(m_allocation.left, m_allocation.top);
	m_visual.m_background.setFillColor(style.m_background.m_background_color);
	m_visual.m_background.setSize(sf::Vector2f(m_allocation.width, m_allocation.height));
	m_visual.m_background.setOutlineColor(style.m_background.m_outline_color);
	m_visual.m_background.setOutlineThickness(style.m_background.m_outline_thickness);
}