#include "GameStateGame.hpp"
#include "GameStateManager.hpp"
#include "Environment.hpp"

#include "Map/BasicMap.hpp"

#include <SFML/Audio.hpp>

GameStateGame::GameStateGame(GameStateManager* state_manager)
	:GameState(state_manager)
{}

void GameStateGame::mt_OnEntry(void)
{
	Environment* l_evironment(m_state_manager->mt_GetEnvironment());

	l_evironment->m_event_manager.mt_Add_Callback(GameStateType::Game, "GAME_KEYBOARD_GameToMainMenu", &GameStateGame::mt_Exit, this);

	m_map = l_evironment->m_map_manager.mt_Get_Resource("GeneratedMap");
	l_evironment->m_sound_system.mt_Pause_Music(m_map->mt_Get_Ambiant_Music_Id());
}

void GameStateGame::mt_OnExit(void)
{
	m_state_manager->mt_GetEnvironment()->m_event_manager.mt_Remove_Callback(GameStateType::Game, "GAME_KEYBOARD_GameToMainMenu");

	m_state_manager->mt_GetEnvironment()->m_sound_system.mt_Stop_Music(m_map->mt_Get_Ambiant_Music_Id());
	m_state_manager->mt_GetEnvironment()->m_map_manager.mt_Release_Resource("GeneratedMap");
}

void GameStateGame::mt_Update(float update_data)
{
	//
}

void GameStateGame::mt_Draw(void)
{
	Environment* l_evironment(m_state_manager->mt_GetEnvironment());

	std::size_t l_count(2);

	l_count = m_map->mt_Get_Layer_Count() + 1;

	for (std::size_t i = 0; i < l_count; i++)
	{
		m_map->mt_Draw_Layer(i, *(l_evironment->m_window.mt_Get_Renderer_Window()));

		l_evironment->m_system_manager.mt_Draw(l_evironment->m_window, i);
	}
}

void GameStateGame::mt_Exit(EventDetails* detail)
{
	m_state_manager->mt_SetState(GameStateType::MainMenu);
}