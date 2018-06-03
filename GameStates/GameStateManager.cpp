#include "GameStateManager.hpp"
#include "GameState.hpp"

GameStateManager::GameStateManager(Environment* environment)
	:m_environment(environment)
{}
GameStateManager::~GameStateManager()
{}

/*void GameStateManager::mt_AddState(const GameStateType& state_id, IGameState* state)
{
	mt_AddState(state_id, static_cast<IState<float>*>(state));
}*/

void GameStateManager::mt_Update(float delta_time_ms)
{
	if (m_current_state != m_states.end())
	{
		m_current_state->second->mt_Update(delta_time_ms);
	}
}

void GameStateManager::mt_Draw(void)
{
	if (m_current_state != m_states.end())
	{
		m_current_state->second->mt_Draw();
	}
}

Environment* GameStateManager::mt_GetEnvironment(void)
{
	return m_environment;
}