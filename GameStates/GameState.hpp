#ifndef _GAME_STATE_HPP
#define _GAME_STATE_HPP 1

#include "Events/Events.hpp"

#include <map>
#include <functional>

class EventManager;

class GameState
{
public:
	GameState();
	virtual ~GameState();

	virtual void onEntry(void);
	virtual void onExit(void);
	void onKeyboardDown(EventData* event_data);
	void onKeyboardUp(EventData* event_data);

protected:
	using CallBackKey = std::map<sf::Keyboard, std::function<void(sf::Event::KeyEvent*)>>;

	EventManager* m_event_manager;
	CallBackKey m_on_key_down;
	CallBackKey m_on_key_up;
};

#endif // _GAME_STATE_HPP
