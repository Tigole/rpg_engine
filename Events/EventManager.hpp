#ifndef _EVENT_MANAGER_HPP
#define _EVENT_MANAGER_HPP 1

#include "Events/Events.hpp"


#include <vector>
#include <set>
#include <map>
#include <functional>

class GameState;

class EventManager
{
public:
	EventManager();
	template<class T>
	void addCallback(const EventType& event_type, void(T::*callback)(EventData*), T* object)
	{
		EventCallBacks::iterator l_event_it;
		std::set<std::function<void(EventData*)>>::iterator l_callback_it;
		std::function<void(EventData*)> l_function;

		if (m_current_state != m_states.end())
		{
			l_function = std::bind(callback, object);

			l_event_it = m_current_state->second.find(event_type);
			if (l_event_it == m_current_state->second.end())
			{
				l_event_it = m_current_state->second.emplace(event_type, std::set<std::function<void(EventData*)>>()).second;
			}

			l_callback_it = l_event_it->second.find(l_function);
			if (l_callback_it == l_event_it->second.end())
			{
				l_event_it->second.emplace(l_function);
			}
		}
	}
	void handleEvent(const sf::Event& sfml_event);
	void update(void);
	void setState(GameState* active_state);

private:
	using EventCallBacks = std::map<EventType, std::set<std::function<void(EventData*)>>>;
	using StatesCallBacks = std::map<GameState*, EventCallBacks>;
	using StatesCallBacksIterator = StatesCallBacks::iterator;

	std::vector<std::pair<EventType, EventData>> m_occured_events;
	StatesCallBacks m_states;
	StatesCallBacksIterator m_current_state;
};


#endif // _EVENT_MANAGER_HPP
