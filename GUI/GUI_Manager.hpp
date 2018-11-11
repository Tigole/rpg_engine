#ifndef _GUI_MANAGER_HPP
#define _GUI_MANAGER_HPP 1

#include "FSM/StateManagement.hpp"
#include "GameStates/GameStateTypes.hpp"
#include "GUI_Event.hpp"
#include "GUI_Interface.hpp"

#include <unordered_map>
#include <stack>

class EventManager;
class XML_Element;
struct EventDetails;
class ParticleSystem;
class ParticleEmitter;

using Events = std::unordered_map<GameStateType, std::stack<EventDataGUI>>;

using Style = std::unordered_map<GUI_Element_State, GUI_Style>;
using StyleContainer = std::unordered_map<std::string, Style>;

using Interface = std::unordered_map<std::string, std::unique_ptr<GUI_Interface>>;
using InterfaceContainer = std::unordered_map<GameStateType, Interface>;

using InterfacePath = std::unordered_map<GameStateType, std::unordered_map<std::string, std::string>>;

class GUI_Manager : public StateDependent<GameStateType>
{
public:
	GUI_Manager(const std::string& resource_path, EventManager* event_manager, Environment* environment, ParticleSystem* particle_system);

	void mt_Show_Mouse(bool show);

	virtual void mt_OnEntry(const GameStateType& state);

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
	bool mt_Load_Path(const XML_Element& element);

	std::string m_resource_path;
	InterfacePath m_paths;
	EventManager* m_event_manager;
	Environment* m_environment;
	ParticleSystem* m_particle_system;
	Events m_events;
	InterfaceContainer m_interfaces;
	StyleContainer m_styles;

	ParticleEmitter* m_mouse_particle_generator;
	bool m_show_mouse;

	static int ms_mouse_elevation;
};

#endif // !_GUI_MANAGER_HPP