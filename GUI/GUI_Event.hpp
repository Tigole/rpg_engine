#ifndef _GUI_EVENT_HPP
#define _GUI_EVENT_HPP 1

enum class EventDataGUIType
{
	None,
	Clicked,
	Released,
	Hover,
};

struct EventDataGUI
{
	EventDataGUIType m_type;
	std::string m_interface_id;
	std::string m_element_id;
};

#endif // !_GUI_EVENT_HPP