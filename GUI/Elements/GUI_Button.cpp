#include "GUI_Button.hpp"

#include "Window/Window.hpp"

#include "Environment.hpp"

GUI_Button::GUI_Button(const std::string& id, GUI_Element* owner)
	:GUI_Element(id, owner)
{}

void GUI_Button::mt_Update(float detla_time_ms)
{
	//
}

void GUI_Button::mt_Draw(Window& target)
{
	auto l_it = m_styles.find(m_current_state);

	if (l_it != m_styles.end())
	{
		target.mt_Get_Renderer_Window()->draw(m_visual.m_background);
		target.mt_Get_Renderer_Window()->draw(m_visual.m_text);
	}
}

void GUI_Button::mt_Apply_Style(const GUI_Style& style)
{
	m_visual.m_background.setPosition(m_position);
	m_visual.m_background.setFillColor(style.m_background.m_background_color);
	m_visual.m_background.setSize(sf::Vector2f(style.m_element.m_size.x, style.m_element.m_size.y));
	m_visual.m_background.setOutlineColor(style.m_background.m_outline_color);
	m_visual.m_background.setOutlineThickness(style.m_background.m_outline_thickness);

	m_visual.m_text.setFont(*(m_environment->m_font_manager.mt_Get_Resource(style.m_text.m_font_id)));
	m_visual.m_text.setPosition(m_position);
	m_visual.m_text.setColor(style.m_text.m_color);
	m_visual.m_text.setCharacterSize(style.m_text.m_size);
}