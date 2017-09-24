#include "EventManager.hpp"

EventManager::EventManager()
 :	m_occured_events(),
	m_states(),
	m_current_state(m_states.end())
{}

void EventManager::mt_Handle_Event(const sf::Event& sfml_event)
{
	std::map<sf::Event::EventType, EventType> l_map;
	std::map<sf::Event::EventType, EventType>::iterator l_map_it;

	l_map[sf::Event::KeyPressed] = EVENT_KEY_DOWN;
	l_map[sf::Event::KeyReleased] = EVENT_KEY_UP;
	l_map[sf::Event::TextEntered] = EVENT_TEXT;

	l_map_it = l_map.find(sfml_event.type);
	if (l_map_it != l_map.end())
	{
		m_occured_events.push_back(std::make_pair(l_map_it->second, EventData(sfml_event)));
	}

	/*
	switch(sfml_event.type)
	{
	case sf::Event::KeyPressed:
		m_occured_events.push_back(std::make_pair(EVENT_KEY_DOWN, EventData(sfml_event)));
		break;
	case sf::Event::KeyReleased:
		m_occured_events.push_back(std::make_pair(EVENT_KEY_UP, EventData(sfml_event)));
		break;
	case sf::Event::TextEntered:
		m_occured_events.push_back(std::make_pair(EVENT_TEXT, EventData(sfml_event)));
		break;
	case sf::Event::Closed:
		break;
	case sf::Event::Resized:
		break;
	case sf::Event::LostFocus:
		break;
	case sf::Event::GainedFocus:
		break;
	case sf::Event::MouseButtonPressed:
		break;
	case sf::Event::MouseButtonReleased:
		break;
	case sf::Event::MouseEntered:
		break;
	case sf::Event::MouseLeft:
		break;
	case sf::Event::MouseMoved:
		break;
	case sf::Event::MouseWheelMoved:
		break;
	case sf::Event::JoystickButtonPressed:
		break;
	case sf::Event::JoystickButtonReleased:
		break;
	case sf::Event::JoystickConnected:
		break;
	case sf::Event::JoystickDisconnected:
		break;
	case sf::Event::JoystickMoved:
		break;
	case sf::Event::MouseWheelScrolled:
		break;
	case sf::Event::TouchBegan:
		break;
	case sf::Event::TouchEnded:
		break;
	case sf::Event::TouchMoved:
		break;
	case sf::Event::SensorChanged:
		break;
	case sf::Event::Count:
		break;
	default:
		break;
	}*/
}

void EventManager::mt_Update(void)
{
	EventCallBacks::iterator l_event_callback_it;

	for (auto& l_event : m_occured_events)
	{
		if (m_current_state != m_states.end())
		{
			l_event_callback_it = m_current_state->second.find(l_event.first);

			if (l_event_callback_it != m_current_state->second.end())
			{
				for (auto& l_function : l_event_callback_it->second)
				{
					l_function(&l_event.second);
				}
			}
		}
	}
}

void EventManager::mt_Set_State(GameState* active_state)
{
	m_current_state = m_states.find(active_state);
	if (m_current_state == m_states.end())
	{
		m_current_state = m_states.emplace(active_state, EventCallBacks()).first;
	}
}
