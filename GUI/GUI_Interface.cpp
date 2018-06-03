#include "GUI_Interface.hpp"
#include "GUI_Element.hpp"
#include "Events/Events.hpp"
#include "GUI_Manager.hpp"

GUI_Interface::GUI_Interface(const std::string& id, GUI_Manager* manager)
	:GUI_Element(id, nullptr),
	m_manager(manager),
	m_is_active(false),
	m_has_focus(false)
{}

void GUI_Interface::mt_Add_Element(GUI_Element* element)
{
	m_elements.emplace(std::make_pair(element->mt_Get_Id(), element));
}

void GUI_Interface::mt_Active(bool activation)
{
	m_is_active = activation;

	if (m_is_active == true)
	{
		for (auto& el : m_elements)
		{
			el.second->mt_Set_State(GUI_Element_State::Neutral);
		}
	}
}

bool GUI_Interface::mt_Is_Active(void) const
{
	return m_is_active;
}

bool GUI_Interface::mt_Has_Focus(void) const
{
	return m_has_focus;
}

void GUI_Interface::mt_On_Click(const sf::Vector2f& mousePos)
{
	EventDataGUI l_event;

	l_event.m_type = EventDataGUIType::Clicked;
	l_event.m_interface_id = m_id;

	for (auto& el : m_elements)
	{
		if (el.second->mt_Is_Inside(mousePos) == true)
		{
			el.second->mt_On_Click(mousePos);
			l_event.m_element_id = el.second->mt_Get_Id();
			m_manager->mt_Add_Event(l_event);
		}
	}
}

void GUI_Interface::mt_On_Release(const sf::Vector2f& mousePos)
{
	EventDataGUI l_event;

	l_event.m_type = EventDataGUIType::Released;
	l_event.m_interface_id = m_id;

	for (auto& el : m_elements)
	{
		el.second->mt_On_Release(mousePos);
		if (el.second->mt_Is_Inside(mousePos) == true)
		{
			l_event.m_element_id = el.second->mt_Get_Id();
			m_manager->mt_Add_Event(l_event);
		}
	}
}

void GUI_Interface::mt_On_Hover(const sf::Vector2f& mousePos)
{
	EventDataGUI l_event;

	l_event.m_type = EventDataGUIType::Hover;
	l_event.m_interface_id = m_id;

	for (auto& el : m_elements)
	{
		el.second->mt_On_Hover(mousePos);
		if (el.second->mt_Get_State() == GUI_Element_State::Focused)
		{
			l_event.m_element_id = el.second->mt_Get_Id();
			m_manager->mt_Add_Event(l_event);
		}
	}
}

void GUI_Interface::mt_On_Leave()
{
	//
}

void GUI_Interface::mt_On_Focus()
{
	//
}

void GUI_Interface::mt_On_Defocus()
{
	//
}


void GUI_Interface::mt_Update(float detla_time_ms)
{
	//
}

void GUI_Interface::mt_Draw(Window& target)
{
	for (auto& el : m_elements)
	{
		el.second->mt_Draw(target);
	}
}

void GUI_Interface::mt_Set_Environment(Environment* env)
{
	GUI_Element::mt_Set_Environment(env);
	for (auto& el : m_elements)
	{
		el.second->mt_Set_Environment(env);
		el.second->mt_Set_State(GUI_Element_State::Neutral);
	}
}

/*void GUI_Interface::mt_On_MouseMove(EventDetails* details)
{
	for (auto& el : m_elements)
	{
		el.second->mt_On_Hover(details->m_position);
	}
}

void GUI_Interface::mt_On_Click(EventDetails* details)
{
	bool stop(false);

	for (auto l_it = m_elements.begin(); (l_it != m_elements.end()) && (stop == false); l_it++)
	{
		if (l_it->second->mt_Is_Inside(details->m_position) == true)
		{
			l_it->second->mt_On_Click(details->m_position);
			stop = true;
		}
	}
}

void GUI_Interface::mt_On_Release(EventDetails* details)
{
	for (auto& el : m_elements)
	{
		el.second->mt_On_Release(details->m_position);
	}
}*/