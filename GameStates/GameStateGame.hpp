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


protected:
	void mt_Exit(EventDetails* detail);
	void mt_PlayerMove(EventDetails* details);
	void mt_PlayerStop(EventDetails* details);
	void mt_Test(EventDetails* details);


	BasicMap* m_map;
};

#endif // !_GAME_STATE_GAME_HPP