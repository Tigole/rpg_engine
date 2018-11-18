#include "GameStateDbg.hpp"
#include "GameStateManager.hpp"
#include "Environment.hpp"

#include "ParticleSystem/Generator/ParticleGeneratorAreaPosition.hpp"
#include "ParticleSystem/Generator/ParticleGeneratorLifeSpan.hpp"
#include "ParticleSystem/Generator/ParticleGeneratorPointPosition.hpp"
#include "ParticleSystem/Generator/ParticleGeneratorRandomColor.hpp"
#include "ParticleSystem/Generator/ParticleGeneratorRandomSize.hpp"
#include "ParticleSystem/Generator/ParticleGeneratorRandomVelocity.hpp"
#include "ParticleSystem/Generator/ParticleGeneratorRangeColor.hpp"
#include "ParticleSystem/Generator/ParticleGeneratorRangeRotation.hpp"
#include "ParticleSystem/Generator/ParticleGeneratorRangeSize.hpp"
#include "ParticleSystem/Generator/ParticleGeneratorTexture.hpp"

GameStateDbg::GameStateDbg(GameStateManager* mngr)
	:GameState(mngr)
{}

void GameStateDbg::mt_OnEntry(void)
{
	RandomGenerator l_rand;
	auto l_Generators = m_state_manager->mt_GetEnvironment()->m_particle_system.mt_Get_Generator_List("Dbg");
	m_Radius = 100.0f;
	m_state_manager->mt_GetEnvironment()->m_event_manager.mt_Add_Callback(GameStateType::Dbg, "GAME_KEYBOARD_GameToMainMenu", &GameStateDbg::mt_Exit, this);
	m_state_manager->mt_GetEnvironment()->m_gui_manager.mt_Show_Mouse(false);

	auto l_Texture = std::make_unique<ParticleGeneratorTexture>();
	auto l_Pos = std::make_unique<ParticleGeneratorPointPosition>();
	auto l_Life = std::make_unique<ParticleGeneratorLifespan>();
	auto l_Col = std::make_unique<ParticleGeneratorRangeColor>();
	auto l_Size = std::make_unique<ParticleGeneratorRangeSize>();
	l_Texture->m_Texture_Id = "Spark";
	l_Life->m_From = 1;
	l_Life->m_To = 1;
	l_Col->m_Start_Color = sf::Color::Yellow;
	l_Col->m_Final_Color = sf::Color::Red;
	l_Size->m_From = 10.0f;
	l_Size->m_To = 0.0f;
	l_Generators->resize(0);
	l_Generators->push_back(std::move(l_Texture));
	l_Generators->push_back(std::move(l_Pos));
	l_Generators->push_back(std::move(l_Life));
	l_Generators->push_back(std::move(l_Col));
	l_Generators->push_back(std::move(l_Size));
}

void GameStateDbg::mt_OnExit(void)
{
	m_state_manager->mt_GetEnvironment()->m_event_manager.mt_Remove_Callback(GameStateType::Dbg, "GAME_KEYBOARD_GameToMainMenu");
}

void GameStateDbg::mt_Draw(void)
{
	Window& l_window(m_state_manager->mt_GetEnvironment()->m_window);
	sf::RenderWindow* l_renderer(l_window.mt_Get_Renderer_Window());

	m_state_manager->mt_GetEnvironment()->m_particle_system.mt_Draw(*l_renderer, 0);
}

void GameStateDbg::mt_Update(float delta_time_ms)
{
	sf::Transform l_transform;
	auto l_screen_size = m_state_manager->mt_GetEnvironment()->m_window.mt_Get_Renderer_Window()->getSize();
	sf::Vector2f l_Point;
	
	l_transform.translate(l_screen_size.x / 2, l_screen_size.y / 2);

	l_Point.x = std::cos(2 * 3.14 / 360 * m_Accumulated_time_s * 100) * m_Radius;
	l_Point.y = std::sin(2 * 3.14 / 360 * m_Accumulated_time_s * 100) * m_Radius;
	l_Point = l_transform.transformPoint(l_Point);

	m_state_manager->mt_GetEnvironment()->m_particle_system.mt_Add_Emitter(GameStateType::Dbg, "Dbg", { l_Point.x, l_Point.y, 0 }, 100, 1);

	m_Accumulated_time_s += delta_time_ms;
	m_state_manager->mt_GetEnvironment()->m_particle_system.mt_Update(delta_time_ms);
}

void GameStateDbg::mt_Exit(EventDetails* detail)
{
	m_state_manager->mt_SetState(GameStateType::MainMenu);
}