#ifndef _EVENT_MANAGER_HPP
#define _EVENT_MANAGER_HPP 1

#include "Events/Events.hpp"
#include "FSM/StateManagement.hpp"
#include "GameStates/GameStateTypes.hpp"
#include "XMLFileLoader.hpp"


#include <vector>
#include <set>
#include <map>
#include <functional>
#include <string>
#include <unordered_map>
#include <memory>

class GameState;

class EventManager : public StateDependent<GameStateType>
{
public:
	EventManager();

	template<class T>
	void mt_Add_Callback(GameStateType game_state, const std::string& event_id, void(T::*callback)(EventDetails*), T* object)
	{
		m_state_callback.emplace(game_state, EventCallBacks()).first->second.emplace(event_id, std::bind(callback, object, std::placeholders::_1));
	}
	template<class T>
	void mt_Add_Callback(const std::string& event_id, void(T::*callback)(EventDetails*), T* object)
	{
		m_no_state_callback.emplace(event_id, std::bind(callback, object, std::placeholders::_1));
	}

	void mt_Remove_Callback(GameStateType game_state, const std::string& event_id);

	void mt_OnEntry(const GameStateType& state);
	void mt_Handle_Event(const sf::Event& sfml_event);
	void mt_Handle_Event(const EventDataGUI& gui_event);
	void mt_Update(void);

	void mt_Load(const std::string& file);

	using Bindings = std::unordered_map<std::string, std::unique_ptr<EventBinding>>;
	using EventCallBacks = std::map<std::string, std::function<void(EventDetails*)>>;
	using StatesCallBacks = std::map<GameStateType, EventCallBacks>;
	using StatesCallBacksIterator = StatesCallBacks::iterator;

private:
	Bindings m_bindings;
	StatesCallBacks m_state_callback;
	EventCallBacks m_no_state_callback;
};


#endif // _EVENT_MANAGER_HPP
