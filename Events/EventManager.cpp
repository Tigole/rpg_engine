#include "EventManager.hpp"
#include <SFML/Main.hpp>

#include "XMLFileLoader.hpp"

EventManager::EventManager()
 : m_state_callback()
{}

void EventManager::mt_Remove_Callback(GameStateType game_state, const std::string& event_id)
{
	auto l_it = m_state_callback.find(game_state);

	if (l_it != m_state_callback.end())
	{
		l_it->second.erase(event_id);
	}
}

void EventManager::mt_Handle_Event(const sf::Event& sfml_event)
{
	std::map<sf::Event::EventType, EventType> l_map;
	std::map<sf::Event::EventType, EventType>::iterator l_map_it;

	for (auto& l_binding_iterator : m_bindings)
	{
		auto& l_bind = l_binding_iterator.second;
		for (auto& l_event_iterator : l_bind->m_events)
		{
			EventType l_event_type(static_cast<EventType>(sfml_event.type));

			if (l_event_type == l_event_iterator.first)
			{
				if (((l_event_type == EventType::EVENT_KEY_UP)
					|| (l_event_type == EventType::EVENT_KEY_DOWN))
					&&(l_event_iterator.second.m_keybord_event.m_keycode == sfml_event.key.code))
				{
					if (l_event_type == EventType::EVENT_KEY_DOWN)
					{
						l_bind->m_details.m_alt_pressed = sfml_event.key.alt;
						l_bind->m_details.m_ctrl_pressed = sfml_event.key.control;
						l_bind->m_details.m_shift_pressed = sfml_event.key.shift;
					}
					else
					{
						l_bind->m_details.m_keycode = sfml_event.key.code;
					}
					l_bind->m_details.m_keycode = sfml_event.key.code;

					l_bind->m_occurence++;
				}
				if (l_event_type == EventType::EVENT_MOUSE_MOVEMENT)
				{
					l_bind->m_details.m_position = sf::Vector2f(sfml_event.mouseMove.x, sfml_event.mouseMove.y);

					l_bind->m_occurence = 1;
				}
				if ((l_event_type == EventType::EVENT_MOUSE_CLICK) || (l_event_type == EventType::EVENT_MOUSE_RELEASE))
				{
					l_bind->m_details.m_position = sf::Vector2f(sfml_event.mouseButton.x, sfml_event.mouseButton.y);
					l_bind->m_details.m_keycode = sfml_event.mouseButton.button;

					l_bind->m_occurence++;
				}
			}
		}
	}
}

void EventManager::mt_Handle_Event(const EventDataGUI& gui_event)
{
	for (auto& l_bind_pair : m_bindings)
	{
		auto& l_bind = l_bind_pair.second;
		for (auto& l_event_pair : l_bind->m_events)
		{
			if ((l_event_pair.first == gui_event.m_type) 
				&& (gui_event.m_interface_id == l_event_pair.second.m_gui_event.m_interface_id) 
				&& (gui_event.m_element_id == l_event_pair.second.m_gui_event.m_element_id))
			{
				l_bind->m_details.m_gui_event.m_element_id = gui_event.m_element_id;
				l_bind->m_details.m_gui_event.m_interface_id = gui_event.m_interface_id;
				l_bind->m_occurence++;
			}
		}
	}
}

void EventManager::mt_OnEntry(const GameStateType& state)
{
	mt_Set_State(state);
}

void EventManager::mt_Update(void)
{
	EventCallBacks::iterator l_event_callback_it;

	for (auto& l_binding_iterator : m_bindings)
	{
		auto& l_binding = l_binding_iterator.second;

		for (auto& l_event_iterator : l_binding->m_events)
		{
			/** !! keycode si evenement avec autre chose que clavier !! **/
		}

		/** Tous les evenements necessaire pour ce bind ont ete actives **/
		if (l_binding->m_occurence == l_binding->m_events.size())
		{
			auto l_current_state(m_state_callback.find(m_current_state));
			auto l_no_state_callback(m_no_state_callback.find(l_binding->m_name));

			l_binding->m_details.m_bind_name = l_binding->m_name;

			if (l_no_state_callback != m_no_state_callback.end())
			{
				l_no_state_callback->second(&l_binding->m_details);
			}

			if (l_current_state != m_state_callback.end())
			{
				auto l_callback_it = l_current_state->second.find(l_binding->m_name);
				if (l_callback_it != l_current_state->second.end())
				{
					l_callback_it->second(&l_binding->m_details);
				}
			}
			l_binding->m_occurence = 0;
			l_binding->m_details.mt_Clear();
		}
	}
}

class EventManager_BindingLoader
{
public:
	EventManager_BindingLoader(EventManager::Bindings& target)
		: m_Target(target)
	{}

	bool mt_Load_Binding(const XML_Element& binding)
	{
		m_bind.m_events.resize(0);
		return binding.mt_Get_Attribute("id", m_bind.m_name);
	}
	bool mt_Load_Binding_Exit(const XML_Element& binding)
	{
		std::unique_ptr<EventBinding> l_ptr;

		l_ptr.reset(new EventBinding(m_bind));

		m_Target.emplace(m_bind.m_name, std::move(l_ptr));

		l_ptr.release();

		return true;
	}
	bool mt_Load_KeyboardUp(const XML_Element& keyboardup)
	{
		bool l_b_ret;
		EventData l_data;

		l_b_ret = keyboardup.mt_Get_Attribute("key", l_data.m_keybord_event.m_keycode);
		if (l_b_ret == true)
		{
			l_data.m_type = EventDataType::EVENT_DATA_TYPE_KEYBOARD;
			m_bind.mt_Append_Event(EventType::EVENT_KEY_UP, l_data);
		}

		return l_b_ret;
	}
	bool mt_Load_KeyboardDonw(const XML_Element& keyboarddown)
	{
		bool l_b_ret;
		EventData l_data;

		l_b_ret = keyboarddown.mt_Get_Attribute("key", l_data.m_keybord_event.m_keycode);
		if (l_b_ret == true)
		{
			l_data.m_type = EventDataType::EVENT_DATA_TYPE_KEYBOARD;
			m_bind.mt_Append_Event(EventType::EVENT_KEY_DOWN, l_data);
		}

		return l_b_ret;
	}
	bool mt_Load_MouseMovement(const XML_Element& mousemovement)
	{
		bool l_b_ret(true);
		EventData l_data;

		l_data.m_type = EventDataType::EVENT_DATA_TYPE_MOUSE;
		m_bind.mt_Append_Event(EventType::EVENT_MOUSE_MOVEMENT, l_data);

		return l_b_ret;
	}
	bool mt_Load_MouseClick(const XML_Element& mouseclick)
	{
		EventData l_data;

		l_data.m_type = EventDataType::EVENT_DATA_TYPE_MOUSE;
		m_bind.mt_Append_Event(EventType::EVENT_MOUSE_CLICK, l_data);

		return true;
	}
	bool mt_Load_MouseRelease(const XML_Element& mouserelease)
	{
		EventData l_data;

		l_data.m_type = EventDataType::EVENT_DATA_TYPE_MOUSE;
		m_bind.mt_Append_Event(EventType::EVENT_MOUSE_RELEASE, l_data);

		return true;
	}
	bool mt_Load_GUIClick(const XML_Element& guiclick)
	{
		return mt_Manage_Load_GUI(EventType::EVENT_GUI_CLICK, guiclick);
	}
	bool mt_Load_GUIRelease(const XML_Element& guirelease)
	{
		return mt_Manage_Load_GUI(EventType::EVENT_GUI_RELEASE, guirelease);
	}
private: 

	bool mt_Manage_Load_GUI(const EventType& event_type, const XML_Element& gui)
	{
		bool l_b_ret(false);
		EventData l_data;

		std::string l_interface_id;
		std::string l_element_id;

		l_b_ret = gui.mt_Get_Attribute("interface_id", l_interface_id);
		if (l_b_ret == true)
		{
			l_b_ret = gui.mt_Get_Attribute("element_id", l_element_id);
		}

		if (l_b_ret == true)
		{
			//l_data.m_gui_event.m_type
			l_data.m_gui_event.m_interface_id = l_interface_id;
			l_data.m_gui_event.m_element_id = l_element_id;
			l_data.m_type = EventDataType::EVENT_DATA_TYPE_GUI;

			m_bind.mt_Append_Event(event_type, l_data);
		}

		return l_b_ret;
	}

	EventManager::Bindings& m_Target;
	EventBinding m_bind;
};

void EventManager::mt_Load(const std::string& file)
{
	EventData l_data;
	EventBinding l_binding;
	EventManager_BindingLoader link(m_bindings);
	XMLFileLoader l_loader;

	l_loader.mt_Set_File(file);
	l_loader.mt_Add_On_Entry_Callback(file, "/Events/Binding", &EventManager_BindingLoader::mt_Load_Binding, &link);
	l_loader.mt_Add_On_Exit_Callback(file, "/Events/Binding", &EventManager_BindingLoader::mt_Load_Binding_Exit, &link);
	l_loader.mt_Add_On_Entry_Callback(file, "/Events/Binding/KeyboardUp", &EventManager_BindingLoader::mt_Load_KeyboardUp, &link);
	l_loader.mt_Add_On_Entry_Callback(file, "/Events/Binding/KeyboardDown", &EventManager_BindingLoader::mt_Load_KeyboardDonw, &link);
	l_loader.mt_Add_On_Entry_Callback(file, "/Events/Binding/MouseMovement", &EventManager_BindingLoader::mt_Load_MouseMovement, &link);
	l_loader.mt_Add_On_Entry_Callback(file, "/Events/Binding/MouseClick", &EventManager_BindingLoader::mt_Load_MouseClick, &link);
	l_loader.mt_Add_On_Entry_Callback(file, "/Events/Binding/MouseRelease", &EventManager_BindingLoader::mt_Load_MouseRelease, &link);
	l_loader.mt_Add_On_Entry_Callback(file, "/Events/Binding/GUIClick", &EventManager_BindingLoader::mt_Load_GUIClick, &link);
	l_loader.mt_Add_On_Entry_Callback(file, "/Events/Binding/GUIRelease", &EventManager_BindingLoader::mt_Load_GUIRelease, &link);

	l_loader.mt_Start();

	l_loader.mt_Wait_For_Ending();

	l_data.m_type = EventDataType::EVENT_DATA_TYPE_MOUSE;
	l_binding.m_name = "GUI_MANAGER_Mouse_Click";
	l_binding.mt_Append_Event(EventType::EVENT_MOUSE_CLICK, l_data);
	m_bindings.emplace(l_binding.m_name, std::make_unique<EventBinding>(l_binding));
	l_binding.m_events.resize(0);
	l_binding.m_name = "GUI_MANAGER_Mouse_Release";
	l_binding.mt_Append_Event(EventType::EVENT_MOUSE_RELEASE, l_data);
	m_bindings.emplace(l_binding.m_name, std::make_unique<EventBinding>(l_binding));
	l_binding.m_events.resize(0);
	l_binding.m_name = "GUI_MANAGER_Mouse_Movement";
	l_binding.mt_Append_Event(EventType::EVENT_MOUSE_MOVEMENT, l_data);
	m_bindings.emplace(l_binding.m_name, std::make_unique<EventBinding>(l_binding));
}
