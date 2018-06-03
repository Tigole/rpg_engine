#include "Events/Events.hpp"

EventBinding::EventBinding()
 :	m_name()
{}

void EventBinding::mt_Append_Event(EventType event_type, const EventData& event_data)
{
	m_events.push_back(std::make_pair(event_type, event_data));
}

EventDataType fn_String_To_EventDataType(const std::string& event_data_type)
{
	EventDataType l_e_Type;

	l_e_Type = EventDataType::EVENT_DATA_TYPE_KEYBOARD;

	return l_e_Type;
}

EventType fn_String_To_EventType(const std::string& event_type)
{
	EventType l_e_type;

	if (event_type == "EVENT_KEY_DOWN")
		l_e_type = EventType::EVENT_KEY_DOWN;
	else if (event_type == "EVENT_KEY_UP")
		l_e_type = EventType::EVENT_KEY_UP;
	else if (event_type == "EVENT_TEXT")
		l_e_type = EventType::EVENT_TEXT;

	return l_e_type;
}


bool operator==(const EventType& a, const EventDataGUIType& b)
{
	bool l_b_Ret;

	l_b_Ret = (((a == EventType::EVENT_GUI_CLICK) && (b == EventDataGUIType::Clicked))
		|| ((a == EventType::EVENT_GUI_RELEASE) && (b == EventDataGUIType::Released)));

	return l_b_Ret;
}