#ifndef _EVENTS_HPP
#define _EVENTS_HPP 1

#include <SFML/Window/Event.hpp>

#include <vector>
#include <set>
#include <map>
#include <functional>

#include "GUI/GUI_Event.hpp"

enum class EventType
{
	EVENT_KEY_DOWN = sf::Event::KeyPressed,
	EVENT_KEY_UP = sf::Event::KeyReleased,
	EVENT_TEXT = sf::Event::TextEntered,
	EVENT_MOUSE_MOVEMENT = sf::Event::MouseMoved,
	EVENT_MOUSE_CLICK = sf::Event::MouseButtonPressed,
	EVENT_MOUSE_RELEASE = sf::Event::MouseButtonReleased,
	EVENT_GUI_CLICK = sf::Event::Count,
	EVENT_GUI_RELEASE,
};

enum class EventDataType
{
	EVENT_DATA_TYPE_KEYBOARD,
	EVENT_DATA_TYPE_MOUSE,
	EVENT_DATA_TYPE_GUI,
};

struct EventDataKeyboard
{
	int m_keycode;
};

struct EventDataMouseMovement
{
	sf::Vector2i m_position;
};

enum class EventDataMouseButtonEnum
{
	EVENT_DATA_MOUSE_BUTTON_LEFT = sf::Event::MouseLeft,
};

struct EventDataMouseButton
{
	EventDataMouseButtonEnum m_button;
};

class EventData
{
public:
	/*EventData();
	EventData(const sf::Event& sfml_event);
	EventData(const EventData& other);
	EventData& operator=(const EventData& other);
	~EventData();*/

	EventDataType m_type;
	EventDataKeyboard m_keybord_event;
	EventDataMouseMovement m_mouse_movement_event;
	EventDataGUI m_gui_event;
};

struct EventDetails
{
	void mt_Clear(void)
	{
		m_alt_pressed = false;
		m_ctrl_pressed = false;
		m_shift_pressed = false;
	}
	int m_keycode;

	bool m_alt_pressed;
	bool m_ctrl_pressed;
	bool m_shift_pressed;

	sf::Vector2f m_position;

	EventDataGUI m_gui_event;
};

class EventBinding
{
public:
	EventBinding();

	void mt_Append_Event(EventType event_type, const EventData& event_data);

	std::string m_name;
	int m_occurence;
	std::vector<std::pair<EventType, EventData>> m_events;
	EventDetails m_details;
	bool m_processed;
};

bool operator==(const EventType& a, const EventDataGUIType& b);
EventDataType fn_String_To_EventDataType(const std::string& event_data_type);
EventType fn_String_To_EventType(const std::string& event_type);

#endif // _EVENTS_HPP
