#ifndef _EVENTS_HPP
#define _EVENTS_HPP 1

#include <SFML/Window/Event.hpp>

#include <vector>
#include <set>
#include <map>
#include <functional>

enum EventType
{
	EVENT_KEY_DOWN = sf::Event::KeyPressed,
	EVENT_KEY_UP = sf::Event::KeyReleased,
	EVENT_TEXT = sf::Event::TextEntered
};

enum EventDataType
{
	EVENT_DATA_TYPE_SFML
};

class EventData
{
public:
	EventData();
	EventData(const sf::Event& sfml_event);
	EventData(const EventData& other);
	EventData& operator=(const EventData& other);
	~EventData();

	EventDataType m_type;
	sf::Event m_sfml_event;
};

class EventBinding
{
public:
	EventBinding(const std::string& event_name);

	void appendEvent(const EventData& event);

	std::string m_name;
	std::vector<std::pair<EventType, EventData>> m_events;
};

#endif // _EVENTS_HPP
