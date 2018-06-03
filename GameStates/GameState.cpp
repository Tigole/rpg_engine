#include "GameState.hpp"

IGameState::IGameState()
{}
IGameState::~IGameState()
{}


GameState::GameState(GameStateManager* state_manager)
	:IGameState(),
	m_state_manager(state_manager),
	m_view()
{}

GameState::~GameState()
{}

GameStateManager* GameState::mt_GetStateManager(void)
{
	return m_state_manager;
}

sf::View& GameState::mt_GetView(void)
{
	return m_view;
}