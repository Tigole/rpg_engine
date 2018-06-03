#include "Game.hpp"
#include "GameStates/GameState.hpp"

#include "GameStates/GameStateIntro.hpp"
#include "GameStates/GameStateGame.hpp"

GameStateType fn_GameStateType_ToEnum(const std::string& type)
{
	GameStateType l_ret((GameStateType)0xffff);
	std::unordered_map<std::string, GameStateType> l_map;
	std::unordered_map<std::string, GameStateType>::iterator l_it;

	l_map["MainMenu"] = GameStateType::MainMenu;
	l_map["Intro"] = GameStateType::Intro;
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

	l_map[GameStateType::SplashScreen] = "";
	l_map[GameStateType::MainMenu] = "MainMenu";
	l_map[GameStateType::Intro] = "Intro";
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

	m_environment.m_window.mt_Create("! The Game !", sf::Vector2u(640, 480));
}

Game::~Game()
{}

void Game::mt_Update(void)
{
	m_environment.m_window.mt_Update();
	m_State_Manager->mt_Update(m_clock.getElapsedTime().asMilliseconds());
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
	m_clock.restart();
}

void Game::mt_Setup_States(void)
{
	m_State_Manager = std::make_unique<GameStateManager>(&m_environment);
	m_Intro_State = std::make_unique<GameStateIntro>(m_State_Manager.get());
	m_Game_State = std::make_unique<GameStateGame>(m_State_Manager.get());


	m_State_Manager->mt_AddDependant(&m_environment.m_event_manager);
	m_State_Manager->mt_AddDependant(&m_environment.m_gui_manager);


	m_State_Manager->mt_AddState(GameStateType::Intro, m_Intro_State.get());
	m_State_Manager->mt_AddState(GameStateType::Game, m_Game_State.get());
	m_State_Manager->mt_SetState(GameStateType::Intro);
}

bool Game::mt_Is_Running() const
{
	return m_environment.m_window.mt_Is_Done() == false;
}