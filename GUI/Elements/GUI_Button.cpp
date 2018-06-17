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