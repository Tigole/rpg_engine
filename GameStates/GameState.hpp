#ifndef _GAME_STATE_HPP
#define _GAME_STATE_HPP 1

#include "Events/Events.hpp"
#include "FSM/StateManagement.hpp"
#include <SFML/Graphics.hpp>

#include <map>
#include <functional>

class GameStateManager;
class EventManager;

class IGameState : public IState
{
public:
	IGameState();
	virtual ~IGameState();

	virtual void mt_Draw(void) = 0;

	virtual GameStateManager* mt_GetStateManager(void) = 0;
	virtual sf::View& mt_GetView(void) = 0;
protected:
};

class GameState : public IGameState
{
public:
	GameState(GameStateManager* state_manager);
	virtual ~GameState();

	virtual GameStateManager* mt_GetStateManager(void);
	virtual sf::View& mt_GetView(void);

protected:
	GameStateManager* m_state_manager;
	sf::View m_view;
};

#endif // _GAME_STATE_HPP
