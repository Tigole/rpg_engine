#include "GameStateGame.hpp"
#include "GameStateManager.hpp"
#include "Environment.hpp"

#include "Map/BasicMap.hpp"

#include "ECS_Game/SystemMovement.hpp"

#include <SFML/Audio.hpp>

GameStateGame::GameStateGame(GameStateManager* state_manager)
	:GameState(state_manager)
{}

void GameStateGame::mt_OnEntry(void)
{
	Environment* l_environment(m_state_manager->mt_GetEnvironment());

	l_environment->m_event_manager.mt_Add_Callback(GameStateType::Game, "GAME_KEYBOARD_GameToMainMenu", &GameStateGame::mt_Exit, this);
	l_environment->m_event_manager.mt_Add_Callback(GameStateType::Game, "PLAYER_DOWN", &GameStateGame::mt_PlayerMove, this);
	l_environment->m_event_manager.mt_Add_Callback(GameStateType::Game, "PLAYER_UP", &GameStateGame::mt_PlayerMove, this);
	l_environment->m_event_manager.mt_Add_Callback(GameStateType::Game, "PLAYER_RIGHT", &GameStateGame::mt_PlayerMove, this);
	l_environment->m_event_manager.mt_Add_Callback(GameStateType::Game, "PLAYER_LEFT", &GameStateGame::mt_PlayerMove, this);
	l_environment->m_event_manager.mt_Add_Callback(GameStateType::Game, "PLAYER_STOP_DOWN", &GameStateGame::mt_PlayerStop, this);
	l_environment->m_event_manager.mt_Add_Callback(GameStateType::Game, "PLAYER_STOP_UP", &GameStateGame::mt_PlayerStop, this);
	l_environment->m_event_manager.mt_Add_Callback(GameStateType::Game, "PLAYER_STOP_RIGHT", &GameStateGame::mt_PlayerStop, this);
	l_environment->m_event_manager.mt_Add_Callback(GameStateType::Game, "PLAYER_STOP_LEFT", &GameStateGame::mt_PlayerStop, this);
	l_environment->m_event_manager.mt_Add_Callback(GameStateType::Game, "TEST", &GameStateGame::mt_Test, this);

	

	m_map = l_environment->m_map_manager.mt_Get_Resource("GeneratedMap");
	l_environment->m_sound_system.mt_Play_Music(m_map->mt_Get_Ambiant_Music_Id());
	l_environment->m_system_manager.mt_Get_System<SystemMovement>(ECS_SystemId::MOVEMENT)->mt_Set_Map(m_map);
}

void GameStateGame::mt_OnExit(void)
{
	m_state_manager->mt_GetEnvironment()->m_event_manager.mt_Remove_Callback(GameStateType::Game, "GAME_KEYBOARD_GameToMainMenu");
	m_state_manager->mt_GetEnvironment()->m_event_manager.mt_Remove_Callback(GameStateType::Game, "PLAYER_DOWN");
	m_state_manager->mt_GetEnvironment()->m_event_manager.mt_Remove_Callback(GameStateType::Game, "PLAYER_UP");
	m_state_manager->mt_GetEnvironment()->m_event_manager.mt_Remove_Callback(GameStateType::Game, "PLAYER_RIGHT");
	m_state_manager->mt_GetEnvironment()->m_event_manager.mt_Remove_Callback(GameStateType::Game, "PLAYER_LEFT");
	m_state_manager->mt_GetEnvironment()->m_event_manager.mt_Remove_Callback(GameStateType::Game, "PLAYER_STOP_DOWN");
	m_state_manager->mt_GetEnvironment()->m_event_manager.mt_Remove_Callback(GameStateType::Game, "PLAYER_STOP_UP");
	m_state_manager->mt_GetEnvironment()->m_event_manager.mt_Remove_Callback(GameStateType::Game, "PLAYER_STOP_RIGHT");
	m_state_manager->mt_GetEnvironment()->m_event_manager.mt_Remove_Callback(GameStateType::Game, "PLAYER_STOP_LEFT");
	m_state_manager->mt_GetEnvironment()->m_event_manager.mt_Remove_Callback(GameStateType::Game, "TEST");

	m_state_manager->mt_GetEnvironment()->m_sound_system.mt_Stop_Music(m_map->mt_Get_Ambiant_Music_Id());
	m_state_manager->mt_GetEnvironment()->m_map_manager.mt_Release_Resource("GeneratedMap");
}

void GameStateGame::mt_Update(float update_data)
{
	m_state_manager->mt_GetEnvironment()->m_system_manager.mt_Update(update_data);
	m_state_manager->mt_GetEnvironment()->m_particle_system.mt_Update(update_data);
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
		l_evironment->m_particle_system.mt_Draw(*(l_evironment->m_window.mt_Get_Renderer_Window()), i);
	}
}

void GameStateGame::mt_Exit(EventDetails* detail)
{
	m_state_manager->mt_SetState(GameStateType::MainMenu);
}

void GameStateGame::mt_PlayerMove(EventDetails* details)
{
	ECS_EntityMessage l_msg;
	ECS_EntityId l_player = m_state_manager->mt_GetEnvironment()->m_entity_manager.mt_Get_Entity("Player");

	if (details->m_bind_name == "PLAYER_DOWN")
	{
		l_msg.m_data.m_direction = Direction::Down;
	}
	else if (details->m_bind_name == "PLAYER_UP")
	{
		l_msg.m_data.m_direction = Direction::Up;
	}
	else if (details->m_bind_name == "PLAYER_RIGHT")
	{
		l_msg.m_data.m_direction = Direction::Right;
	}
	else if (details->m_bind_name == "PLAYER_LEFT")
	{
		l_msg.m_data.m_direction = Direction::Left;
	}

	l_msg.m_sender = l_player;
	l_msg.m_id = ECS_EntityMessageId::MoveRqst;
		
	m_state_manager->mt_GetEnvironment()->m_system_manager.mt_Get_MessageHandler()->mt_Dispatch(l_msg);
}

void GameStateGame::mt_PlayerStop(EventDetails* details)
{
	ECS_EntityMessage l_msg;
	ECS_EntityId l_player = m_state_manager->mt_GetEnvironment()->m_entity_manager.mt_Get_Entity("Player");

	if (details->m_bind_name == "PLAYER_STOP_DOWN")
	{
		l_msg.m_data.m_direction = Direction::Down;
	}
	else if (details->m_bind_name == "PLAYER_STOP_UP")
	{
		l_msg.m_data.m_direction = Direction::Up;
	}
	else if (details->m_bind_name == "PLAYER_STOP_RIGHT")
	{
		l_msg.m_data.m_direction = Direction::Right;
	}
	else if (details->m_bind_name == "PLAYER_STOP_LEFT")
	{
		l_msg.m_data.m_direction = Direction::Left;
	}

	l_msg.m_sender = l_player;
	l_msg.m_id = ECS_EntityMessageId::StopMove;

	m_state_manager->mt_GetEnvironment()->m_system_manager.mt_Get_MessageHandler()->mt_Dispatch(l_msg);
}

#include <iostream>
#include "ECS_Game/ComponentPosition.hpp"
void GameStateGame::mt_Test(EventDetails* details)
{
	auto& l_particle_system = m_state_manager->mt_GetEnvironment()->m_particle_system;
	auto& l_entity_mngr = m_state_manager->mt_GetEnvironment()->m_entity_manager;
	auto l_player_pos = l_entity_mngr.mt_Get_Component<ComponentPosition>(l_entity_mngr.mt_Get_Entity("Player"), ECS_ComponentId::POSITION);
	auto l_target_pos = l_entity_mngr.mt_Get_Component<ComponentPosition>(l_entity_mngr.mt_Get_Entity("Carapuce"), ECS_ComponentId::POSITION);

	/*auto l_generator_list = l_particle_system.mt_Get_Generator_List("test");
	l_generator_list->push_back(std::make_unique<ParticleGenerator>());*/

	l_particle_system.mt_Add_Emitter(GameStateType::Game, "Flame", { l_player_pos->mt_Get_Current_Position().x, l_player_pos->mt_Get_Current_Position().y, 1.0f }, 10, 15);
}