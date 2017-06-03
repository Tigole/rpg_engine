#include "Events/Events.hpp"

EventData::EventData()
 :	m_type(EVENT_DATA_TYPE_SFML),
	m_sfml_event()
{}

EventData::EventData(const sf::Event& sfml_event)
 :	m_type(EVENT_DATA_TYPE_SFML),
	m_sfml_event(sfml_event)
{}

EventData::EventData(const EventData& other)
 :	m_type(other.m_type),
	m_sfml_event()
{}

EventData& EventData::operator=(const EventData& other)
{
	m_type = other.m_type;
	return *this;
}

EventData::~EventData()
{}


EventBinding::EventBinding(const std::string& event_name)
 :	m_name(event_name)
{}

void EventBinding::appendEvent(const EventData& event)
{
	//
}
