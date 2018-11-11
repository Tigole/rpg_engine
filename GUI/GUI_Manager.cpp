#include "GUI_Manager.hpp"

#include "Events/EventManager.hpp"

#include "XMLFileLoader.hpp"
#include "GUI_Manager_Loader.hpp"

#include "ParticleSystem/ParticleSystem.hpp"

#include "Window/Window.hpp"

int GUI_Manager::ms_mouse_elevation = 50;

GUI_Manager::GUI_Manager(const std::string& resource_path, EventManager* event_manager, Environment* environment, ParticleSystem* particle_system)
	:m_event_manager(event_manager), m_environment(environment), m_resource_path(resource_path + "Data/"), m_particle_system(particle_system), m_show_mouse(true)
{
	m_event_manager->mt_Add_Callback("GUI_MANAGER_Mouse_Click", &GUI_Manager::mt_On_Click, this);
	m_event_manager->mt_Add_Callback("GUI_MANAGER_Mouse_Release", &GUI_Manager::mt_On_Release, this);
	m_event_manager->mt_Add_Callback("GUI_MANAGER_Mouse_Movement", &GUI_Manager::mt_On_MouseMove, this);
}

void GUI_Manager::mt_Show_Mouse(bool show)
{
	m_show_mouse = show;
}

void GUI_Manager::mt_OnEntry(const GameStateType& state)
{
	auto l_state = m_interfaces.find(m_current_state);
	auto l_path = m_paths.end();

	if (l_state != m_interfaces.end())
	{
		for (auto& l_interface : l_state->second)
		{
			l_interface.second->mt_Active(false);
			l_interface.second->mt_On_Release(sf::Vector2f(0.0f, 0.0f));
		}
	}

	m_particle_system->mt_Remove_Emitter(m_mouse_particle_generator);

	mt_Set_State(state);

	l_path = m_paths.find(m_current_state);
	if (l_path != m_paths.end())
	{
		for (auto& l_interface_ : l_path->second)
		{
			GUI_Interface* l_interface = mt_Get_Interface(m_current_state, l_interface_.first);

			if (l_interface != nullptr)
			{
				l_interface->mt_Redraw();
				l_interface->mt_Active(true);
			}
		}
	}
}

void GUI_Manager::mt_Add_Style(const std::string& style_id, const GUI_Element_State& state, const GUI_Style& style)
{
	auto l_style = m_styles.find(style_id);

	if (l_style == m_styles.end())
	{
		l_style = m_styles.emplace(style_id, Style()).first;
	}

	l_style->second.emplace(state, style);
}

const Style* GUI_Manager::mt_Get_Style(const std::string& style_id) const
{
	const Style* l_ret(nullptr);
	auto l_stryle = m_styles.find(style_id);

	if (l_stryle != m_styles.end())
	{
		l_ret = &l_stryle->second;
	}

	return l_ret;
}

void GUI_Manager::mt_Add_Interface(const GameStateType& state, GUI_Interface* inter)
{
	auto l_state = m_interfaces.find(state);

	if (l_state == m_interfaces.end())
	{
		l_state = m_interfaces.emplace(state, Interface()).first;
	}

	l_state->second.emplace(inter->mt_Get_Id(), inter).first->second->mt_Set_Environment(m_environment);
}

GUI_Interface* GUI_Manager::mt_Get_Interface(const GameStateType& state, const std::string& interface_id)
{
	GUI_Interface* l_ret(nullptr);
	auto l_state(m_interfaces.end());
	GUI_Manager_Interface_Loader l_loader;
	XMLFileLoader l_xml_loader;
	auto l_path_state = m_paths.find(m_current_state);

	if (l_path_state != m_paths.end())
	{
		auto& l_path = l_path_state->second.find(interface_id);

		if (l_path != l_path_state->second.end())
		{
			l_loader.mt_Prepare(m_resource_path + l_path->second, l_xml_loader, this);

			l_xml_loader.mt_Start();
			l_xml_loader.mt_Wait_For_Ending();
		}
	}

	l_state = m_interfaces.find(m_current_state);
	
	if (l_state != m_interfaces.end())
	{
		auto l_interface(l_state->second.find(interface_id));
		if (l_interface != l_state->second.end())
		{
			l_ret = l_interface->second.get();
		}
	}

	return l_ret;
}

void GUI_Manager::mt_Add_Event(const EventDataGUI& gui_event)
{
	m_events[m_current_state].push(gui_event);
}

bool GUI_Manager::mt_Poll_Event(EventDataGUI& gui_event)
{
	bool l_b_ret(false);
	if (m_events[m_current_state].size() != 0)
	{
		gui_event = m_events[m_current_state].top();
		m_events[m_current_state].pop();
		l_b_ret = true;
	}
	return l_b_ret;
}

void GUI_Manager::mt_Load_Interfaces(const std::string& conf_file)
{
	XMLFileLoader l_xml_loader;

	l_xml_loader.mt_Set_File(conf_file);
	l_xml_loader.mt_Add_On_Entry_Callback(conf_file, "/Interfaces/Interface", &GUI_Manager::mt_Load_Path, this);

	l_xml_loader.mt_Start();
	l_xml_loader.mt_Wait_For_Ending(100);
}

void GUI_Manager::mt_Load_Styles(const std::string& conf_file)
{
	GUI_Manager_Style_Loader l_loader;
	XMLFileLoader l_xml_loader;

	l_loader.mt_Prepare(conf_file, l_xml_loader, this);

	l_xml_loader.mt_Start();
	l_xml_loader.mt_Wait_For_Ending(100);
}

void GUI_Manager::mt_On_MouseMove(EventDetails* details)
{
	auto l_state = m_interfaces.find(m_current_state);

	if (m_show_mouse == true)
	{
		m_particle_system->mt_Remove_Emitter(m_mouse_particle_generator);
		m_mouse_particle_generator = m_particle_system->mt_Add_Emitter(m_current_state, "Mouse", sf::Vector3f(details->m_position.x, details->m_position.y, ms_mouse_elevation), 100, -1);

		std::cout << "{ " << details->m_position.x << ", " << details->m_position.y << " }\n";
	}

	if (l_state != m_interfaces.end())
	{
		for (auto& l_interface : l_state->second)
		{
			if (l_interface.second->mt_Is_Active() == true)
			{
				l_interface.second->mt_On_Hover(details->m_position);
			}
		}
	}
}

void GUI_Manager::mt_On_Click(EventDetails* details)
{
	auto l_state = m_interfaces.find(m_current_state);

	if (l_state != m_interfaces.end())
	{
		for (auto& l_interface : l_state->second)
		{
			if (l_interface.second->mt_Is_Active() == true)
			{
				l_interface.second->mt_On_Click(details->m_position);
			}
		}
	}
}

void GUI_Manager::mt_On_Release(EventDetails* details)
{
	auto l_state = m_interfaces.find(m_current_state);

	if (l_state != m_interfaces.end())
	{
		for (auto& l_interface : l_state->second)
		{
			if (l_interface.second->mt_Is_Active() == true)
			{
				l_interface.second->mt_On_Release(details->m_position);
			}
		}
	}
}

void GUI_Manager::mt_On_Text_Entered(EventDetails* details)
{
	//
}

void GUI_Manager::mt_On_Key_Navigation(EventDetails* details)
{
	//
}

void GUI_Manager::mt_Update(float delta_time_ms)
{
	auto l_state = m_interfaces.find(m_current_state);

	if (l_state != m_interfaces.end())
	{
		for (auto& l_interface : l_state->second)
		{
			if (l_interface.second->mt_Is_Active() == true)
			{
				l_interface.second->mt_Update(delta_time_ms);
			}
		}
	}
}

void GUI_Manager::mt_Draw(Window& target)
{
	auto l_state = m_interfaces.find(m_current_state);
	sf::RenderWindow* l_render_window(target.mt_Get_Renderer_Window());
	sf::View l_current_view(l_render_window->getView());

	if (l_state != m_interfaces.end())
	{
		l_render_window->setView(l_render_window->getDefaultView());

		for (auto& l_interface : l_state->second)
		{
			if (l_interface.second->mt_Is_Active() == true)
			{
				l_interface.second->mt_Draw(target);
			}
		}

		l_render_window->setView(l_current_view);
	}

	if (m_show_mouse == true)
	{
		m_particle_system->mt_Draw(*l_render_window, ms_mouse_elevation);
	}
}

Environment* GUI_Manager::mt_Get_Environment(void)
{
	return m_environment;
}

bool GUI_Manager::mt_Load_Path(const XML_Element& element)
{
	bool l_b_ret;
	std::string l_id;
	std::string l_path;
	GameStateType l_game_state;

	l_b_ret = element.mt_Get_Attribute("id", l_id);

	if (l_b_ret == true)
	{
		l_b_ret = element.mt_Get_Attribute("path", l_path);
	}

	if (l_b_ret == true)
	{
		l_b_ret = element.mt_Get_Attribute("game_state", l_game_state, fn_GameStateType_ToEnum);
	}

	if (l_b_ret == true)
	{
		m_paths[l_game_state].emplace(l_id, l_path);
	}

	return l_b_ret;
}