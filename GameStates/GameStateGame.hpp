#ifndef _GAME_STATE_GAME_HPP
#define _GAME_STATE_GAME_HPP 1

#include "GameState.hpp"

#include <SFML/Audio.hpp>

class BasicMap;

class EventDetails;

class GameStateGame : public GameState
{
public:
	GameStateGame(GameStateManager* state_manager);

	virtual void mt_OnEntry(void);
	virtual void mt_OnExit(void);
	virtual void mt_Update(float update_data);
	virtual void mt_Draw(void);

	void mt_Exit(EventDetails* detail);

protected:
	BasicMap* m_map;
};

#endif // !_GAME_STATE_GAME_HPP