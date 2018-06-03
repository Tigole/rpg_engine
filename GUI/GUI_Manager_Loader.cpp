#include "GUI_Manager_Loader.hpp"

#include "XMLFileLoader.hpp"
#include "GUI_Manager.hpp"

#include "GUI_Element.hpp"
#include "Elements/GUI_Button.hpp"
#include "GUI_Interface.hpp"

#include "Environment.hpp"

GUI_Manager_Interface_Loader::~GUI_Manager_Interface_Loader()
{
	for (auto& el : m_elements)
		delete el;
}

void GUI_Manager_Interface_Loader::mt_Prepare(const std::string& file_name, XMLFileLoader& loader, GUI_Manager* target)
{
	m_target = target;

	loader.mt_Set_File(file_name);
	loader.mt_Add_On_Entry_Callback(file_name, "/Interfaces/Interface", &GUI_Manager_Interface_Loader::mt_Load_Interface, this);
	loader.mt_Add_On_Entry_Callback(file_name, "/Interfaces/Interface/Button", &GUI_Manager_Interface_Loader::mt_Load_Button, this);

	loader.mt_Add_On_Exit_Callback(file_name, "/Interfaces/Interface", &GUI_Manager_Interface_Loader::mt_Finalize_Interface, this);
}

bool GUI_Manager_Interface_Loader::mt_Load_Button(const XML_Element& button)
{
	bool l_b_ret(false);
	std::string l_id;
	std::string text_id;
	std::string l_style_id;
	GUI_Button* l_button;
	const Style* l_style(nullptr);
	sf::Vector2f l_pos;

	l_b_ret = button.mt_Get_Attribute("id", l_id);

	if (l_b_ret == true)
	{
		l_b_ret = button.mt_Get_Attribute("text_id", text_id);
	}

	if (l_b_ret == true)
	{
		l_b_ret = button.mt_Get_Attribute("style_id", l_style_id);
	}

	if (l_b_ret == true)
	{
		l_b_ret = button.mt_Get_Attribute("x_pos", l_pos.x);
	}

	if (l_b_ret == true)
	{
		l_b_ret = button.mt_Get_Attribute("y_pos", l_pos.y);
	}

	if (l_b_ret == true)
	{
		l_style = m_target->mt_Get_Style(l_style_id);

		l_b_ret = (l_style != nullptr);
	}

	if (l_b_ret == true)
	{
		l_button = new GUI_Button(l_id, m_interface);

		l_button->mt_Set_Text(m_target->mt_Get_Environment()->m_string_manager.mt_Get_String(m_target->mt_Get_Environment()->m_string_manager.mt_Get_Current_Lang(), text_id));
		l_button->mt_Set_Position(l_pos);
		
		for (auto& s : *l_style)
		{
			l_button->mt_Set_Style(s.first, s.second);
		}

		m_interface->mt_Add_Element(l_button);
	}

	return l_b_ret;
}

bool GUI_Manager_Interface_Loader::mt_Load_Interface(const XML_Element& element)
{
	bool l_b_ret(false);
	std::string l_id;

	l_b_ret = element.mt_Get_Attribute("id", l_id);

	if (l_b_ret == true)
	{
		m_interface = new GUI_Interface(l_id, m_target);
	}

	if (l_b_ret == true)
	{
		l_b_ret = element.mt_Get_Attribute("game_state", m_game_state, &fn_GameStateType_ToEnum);
	}

	return l_b_ret;
}

bool GUI_Manager_Interface_Loader::mt_Finalize_Interface(const XML_Element& element)
{
	bool l_b_ret(false);

	if (m_interface != nullptr)
	{
		m_target->mt_Add_Interface(m_game_state, m_interface);

		l_b_ret = true;
	}

	return l_b_ret;
}









GUI_Manager_Style_Loader::~GUI_Manager_Style_Loader()
{}

void GUI_Manager_Style_Loader::mt_Prepare(const std::string& file_name, XMLFileLoader& loader, GUI_Manager* target)
{
	m_target = target;

	loader.mt_Set_File(file_name);

	loader.mt_Add_On_Entry_Callback(file_name, "/Styles/Style", &GUI_Manager_Style_Loader::mt_Load_Style, this);
	loader.mt_Add_On_Entry_Callback(file_name, "/Styles/Style/State", &GUI_Manager_Style_Loader::mt_Load_State, this);
	loader.mt_Add_On_Entry_Callback(file_name, "/Styles/Style/State/Element", &GUI_Manager_Style_Loader::mt_Load_Element, this);
	loader.mt_Add_On_Entry_Callback(file_name, "/Styles/Style/State/Text", &GUI_Manager_Style_Loader::mt_Load_Text, this);
	loader.mt_Add_On_Entry_Callback(file_name, "/Styles/Style/State/Background", &GUI_Manager_Style_Loader::mt_Load_Background, this);

	loader.mt_Add_On_Exit_Callback(file_name, "/Styles/Style/State", &GUI_Manager_Style_Loader::mt_Finalize_State, this);
}

bool GUI_Manager_Style_Loader::mt_Load_Style(const XML_Element& style)
{
	bool l_b_ret(false);

	mt_Reset_Style();

	l_b_ret = style.mt_Get_Attribute("id", m_style_id);

	return l_b_ret;
}

bool GUI_Manager_Style_Loader::mt_Load_State(const XML_Element& state)
{
	bool l_b_ret(true);

	state.mt_Get_Attribute("id", m_state_id, &fn_GUIElementState_ToEnum);

	return l_b_ret;
}
bool GUI_Manager_Style_Loader::mt_Load_Element(const XML_Element& element)
{
	bool l_b_ret(true);

	element.mt_Get_Attribute("x_size", m_style.m_element.m_size.x);
	element.mt_Get_Attribute("y_size", m_style.m_element.m_size.y);

	return l_b_ret;
}

bool GUI_Manager_Style_Loader::mt_Load_Text(const XML_Element& text)
{
	bool l_b_ret(true);
	
	text.mt_Get_Attribute("font_id", m_style.m_text.m_font_id);
	text.mt_Get_Attribute("char_size", m_style.m_text.m_size);
	mt_Load_Color(text, m_style.m_text.m_color);

	return l_b_ret;
}

bool GUI_Manager_Style_Loader::mt_Load_Background(const XML_Element& background)
{
	bool l_b_ret(true);

	mt_Load_Color(background, m_style.m_background.m_background_color);

	return l_b_ret;
}

bool GUI_Manager_Style_Loader::mt_Finalize_State(const XML_Element& state)
{
	bool l_b_ret(true);

	m_target->mt_Add_Style(m_style_id, m_state_id, m_style);

	return l_b_ret;
}

void GUI_Manager_Style_Loader::mt_Load_Color(const XML_Element& element, sf::Color& color)
{
	int r, g, b, a;
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;

	element.mt_Get_Attribute("r", r);
	element.mt_Get_Attribute("g", g);
	element.mt_Get_Attribute("b", b);
	element.mt_Get_Attribute("a", a);

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

void GUI_Manager_Style_Loader::mt_Reset_Style(void)
{
	m_style.m_text.m_color = sf::Color(255, 250, 205);
	m_style.m_text.m_font_id = "";
	m_style.m_text.m_size = 0;
	m_style.m_element.m_size = sf::Vector2u(0, 0);
	m_style.m_background.m_background_color = sf::Color(0, 51, 102);
	m_style.m_background.m_outline_color = m_style.m_text.m_color;
	m_style.m_background.m_outline_thickness = 1.0f;
}