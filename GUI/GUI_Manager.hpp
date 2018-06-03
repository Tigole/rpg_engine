#ifndef _GUI_MANAGER_HPP
#define _GUI_MANAGER_HPP 1

#include "FSM/StateManagement.hpp"
#include "GameStates/GameStateTypes.hpp"
#include "GUI_Event.hpp"
#include "GUI_Interface.hpp"

#include <unordered_map>
#include <stack>

class EventManager;
struct EventDetails;

using Events = std::unordered_map<GameStateType, std::stack<EventDataGUI>>;

using Style = std::unordered_map<GUI_Element_State, GUI_Style>;
using StyleContainer = std::unordered_map<std::string, Style>;

using Interface = std::unordered_map<std::string, std::unique_ptr<GUI_Interface>>;
using InterfaceContainer = std::unordered_map<GameStateType, Interface>;

class GUI_Manager : public StateDependent<GameStateType>
{
public:
	GUI_Manager(EventManager* event_manager, Environment* environment);

	void mt_OnEntry(const GameStateType& state);

	void mt_Add_Style(const std::string& style_id, const GUI_Element_State& state, const GUI_Style& style);
	const Style* mt_Get_Style(const std::string& style_id) const;

	void mt_Add_Interface(const GameStateType& state, GUI_Interface* inter);
	GUI_Interface* mt_Get_Interface(const GameStateType& state, const std::string& interface_id);

	void mt_Add_Event(const EventDataGUI& gui_event);
	bool mt_Poll_Event(EventDataGUI& gui_event);

	void mt_Load_Interfaces(const std::string& conf_file);
	void mt_Load_Styles(const std::string& conf_file);

	void mt_On_MouseMove(EventDetails* details);
	void mt_On_Click(EventDetails* details);
	void mt_On_Release(EventDetails* details);
	void mt_On_Text_Entered(EventDetails* details);
	void mt_On_Key_Navigation(EventDetails* details);

	void mt_Update(float delta_time_ms);
	void mt_Draw(Window& target);

	Environment* mt_Get_Environment(void);

private:
	EventManager* m_event_manager;
	Environment* m_environment;
	Events m_events;
	InterfaceContainer m_interfaces;
	StyleContainer m_styles;
};

#endif // !_GUI_MANAGER_HPP