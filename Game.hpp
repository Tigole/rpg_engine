#ifndef _GAME_HPP
#define _GAME_HPP 1

#include <string>

#include "ECS_Core/ECS_SystemManager.hpp"
#include "ECS_Core/ECS_EntityManager.hpp"
#include "Environment.hpp"
#include "Window/Window.hpp"
#include "GameStates/GameStateManager.hpp"

#include <memory>

using BasicMapManager = MapManager<BasicMap, BasicMapLoader>;
using GameStateContainer = std::unordered_map<GameStateType, std::unique_ptr<GameState>>;

class Game
{
public:
	Game(const std::string& resource_path);
	~Game();
	void mt_Update(void);
	void mt_Render(void);
	void mt_LateUpdate(void);
	bool mt_Is_Running() const;

private:
	Environment m_environment;

	std::unique_ptr<GameStateManager> m_State_Manager;
	sf::Clock m_clock;
	float m_elapsed_time_s;

	GameStateContainer m_game_states;

	void mt_Setup_States(void);
};

#endif // !_GAME_HPP