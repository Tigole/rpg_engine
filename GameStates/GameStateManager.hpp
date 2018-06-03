#ifndef _GAME_STATE_MANAGER_HPP
#define _GAME_STATE_MANAGER_HPP 1

#include <memory>
#include <unordered_set>
#include <unordered_map>

#include "GameStateTypes.hpp"
#include "FSM/StateManagement.hpp"

class IGameState;
class Environment;

class GameStateManager : public StateManager<float, GameStateType>
{
public:
	GameStateManager(Environment* environment);
	virtual ~GameStateManager();

	void mt_Update(float delta_time_ms);
	//void mt_AddState(const GameStateType& state_id, IGameState* state);

	void mt_Draw(void);
	Environment* mt_GetEnvironment(void);

protected:
	Environment* m_environment;
};

#endif // !_GAME_STATE_MANAGER_HPP