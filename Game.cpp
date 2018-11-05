#include "Game.hpp"
#include "GameStates/GameState.hpp"

#include "GameStates/GameStateIntro.hpp"
#include "GameStates/GameStateGame.hpp"
#include "GameStates/GameStateMainMenu.hpp"

#include <iostream>

static unsigned int gs_step = 0;

GameStateType fn_GameStateType_ToEnum(const std::string& type)
{
	GameStateType l_ret((GameStateType)0xffff);
	std::unordered_map<std::string, GameStateType> l_map;
	std::unordered_map<std::string, GameStateType>::iterator l_it;

	l_map["MainMenu"] = GameStateType::MainMenu;
	//l_map["Intro"] = GameStateType::Intro;
	l_map["Game"] = GameStateType::Game;

	l_it = l_map.find(type);
	if (l_it != l_map.end())
	{
		l_ret = l_it->second;
	}

	return l_ret;
}

std::string fn_GameStateType_ToString(const GameStateType& type)
{
	std::string l_ret;
	std::unordered_map<GameStateType, std::string> l_map;
	std::unordered_map<GameStateType, std::string>::iterator l_it;

	//l_map[GameStateType::SplashScreen] = "";
	l_map[GameStateType::MainMenu] = "MainMenu";
	//l_map[GameStateType::Intro] = "Intro";
	l_map[GameStateType::Game] = "Game";

	l_it = l_map.find(type);
	if (l_it != l_map.end())
	{
		l_ret = l_it->second;
	}

	return l_ret;
}

Game::Game(const std::string& resource_path)
	: m_environment(resource_path)
{
	m_environment.mt_Load("Environment.xml");
	m_clock.restart();
	mt_Setup_States();

	m_environment.m_window.mt_Create("! The Game !", sf::Vector2u(800 /*640*/, 600 /*480*/));
	m_State_Manager->mt_SetState(GameStateType::MainMenu);
}

Game::~Game()
{}

void Game::mt_Update(void)
{
	float l_delta_time_s = m_elapsed_time_s;
	//std::cout << "Step: " << gs_step << '\n';
	m_environment.m_window.mt_Update();
	m_State_Manager->mt_Update(l_delta_time_s);
	m_environment.m_gui_manager.mt_Update(l_delta_time_s);
}

void Game::mt_Render(void)
{
	m_environment.m_window.mt_Begin_Draw();

	m_State_Manager->mt_Draw();
	m_environment.m_gui_manager.mt_Draw(m_environment.m_window);

	m_environment.m_window.mt_End_Draw();
}

void Game::mt_LateUpdate(void)
{
	m_elapsed_time_s = m_clock.restart().asSeconds();
	//m_elapsed_time_s = 0.002;
	gs_step++;
}

void Game::mt_Setup_States(void)
{
	m_State_Manager = std::make_unique<GameStateManager>(&m_environment);

	m_game_states.emplace(GameStateType::MainMenu, std::make_unique<GameStateMainMenu>(m_State_Manager.get()));
	m_game_states.emplace(GameStateType::Game, std::make_unique<GameStateGame>(m_State_Manager.get()));

	for (auto& l_game_state : m_game_states)
	{
		m_State_Manager->mt_AddState(l_game_state.first, l_game_state.second.get());
	}

	m_State_Manager->mt_AddDependant(&m_environment.m_event_manager);
	m_State_Manager->mt_AddDependant(&m_environment.m_gui_manager);
	m_State_Manager->mt_AddDependant(&m_environment.m_particle_system);
}

bool Game::mt_Is_Running() const
{
	return m_environment.m_window.mt_Is_Done() == false;
}