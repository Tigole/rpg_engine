#include "GUI_Element.hpp"



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


GUI_Element::GUI_Element(const std::string& id, GUI_Element* owner)
	:m_id(id), m_owner(owner), m_current_state(GUI_Element_State::Neutral)
{
	//
}

void GUI_Element::mt_Set_Position(const sf::Vector2f& pos)
{
	m_position = pos;
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
	m_current_state = state;
	auto l_style = m_styles.find(m_current_state);

	if (l_style != m_styles.end())
	{
		mt_Apply_Style(l_style->second);
	}
}

void GUI_Element::mt_On_Click(const sf::Vector2f& mousePos)
{
	mt_Set_State(GUI_Element_State::Clicked);
}

void GUI_Element::mt_On_Release(const sf::Vector2f& mousePos)
{
	if (m_current_state == GUI_Element_State::Clicked)
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
}

void GUI_Element::mt_On_Hover(const sf::Vector2f& mousePos)
{
	bool l_is_inside(mt_Is_Inside(mousePos));
	if ((m_current_state == GUI_Element_State::Neutral) && (l_is_inside == true))
	{
		mt_Set_State(GUI_Element_State::Focused);
	}
	if ((m_current_state == GUI_Element_State::Focused) && (l_is_inside == false))
	{
		mt_Set_State(GUI_Element_State::Neutral);
	}
}

sf::FloatRect GUI_Element::mt_Get_Screen_Space(void) const
{
	sf::FloatRect l_ret;
	auto l_style = m_styles.find(m_current_state);

	if (l_style != m_styles.end())
	{
		l_ret.left = m_position.x;
		l_ret.top = m_position.y;
		l_ret.width = l_style->second.m_element.m_size.x;
		l_ret.height = l_style->second.m_element.m_size.y;

		if (m_owner != nullptr)
		{
			l_ret.left += m_owner->mt_Get_Screen_Position().x;
			l_ret.top += m_owner->mt_Get_Screen_Position().y;
		}
	}

	return l_ret;
}

sf::Vector2f GUI_Element::mt_Get_Required_Space(void) const
{
	sf::Vector2f l_ret;

	for (auto& l_style : m_styles)
	{
		if (l_ret.x < l_style.second.m_element.m_size.x)
		{
			l_ret.x = l_style.second.m_element.m_size.x;
		}

		if (l_ret.y < l_style.second.m_element.m_size.y)
		{
			l_ret.y = l_style.second.m_element.m_size.y;
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
	sf::Vector2f l_ret(m_position);

	if (m_owner != nullptr)
	{
		l_ret += mt_Get_Screen_Position();
	}

	return l_ret;
}

void GUI_Element::mt_Set_Text(const std::string& text)
{
	m_visual.m_text.setString(text);
}