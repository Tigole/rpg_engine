#ifndef _GAME_STATE_DBG_HPP
#define _GAME_STATE_DBG_HPP 1

#include "GameState.hpp"

class ParticleEmitter;

class GameStateDbg : public GameState
{
public:
	GameStateDbg(GameStateManager* mngr);
	virtual void mt_Draw(void);
	virtual void mt_OnEntry(void);
	virtual void mt_OnExit(void);

	virtual void mt_Update(float delta_time_ms);

private:
	void mt_Exit(EventDetails* detail);

	float m_Accumulated_time_s;
	float m_Radius;
};


#endif // !_GAME_STATE_DBG_HPP