#include "GameStateIntro.hpp"
#include "GameStateManager.hpp"
#include "Environment.hpp"

GameStateIntro::GameStateIntro(GameStateManager* state_manager)
	: GameState(state_manager),
	m_texture_id("Intro"),
	m_text_to_display("Intro v0.0 !")
{
	m_Font.loadFromFile("C:/Windows/Fonts/arial.ttf");
}

void GameStateIntro::mt_OnEntry(void)
{
	sf::Vector2f l_view_size(m_view.getSize());
	Environment* l_environement(m_state_manager->mt_GetEnvironment());

	sf::Texture* l_texture;

	m_sprite.setTexture(*(l_environement->m_texture_manager.mt_Get_Resource(m_texture_id)));

	l_environement->m_event_manager.mt_Add_Callback(GameStateType::Intro, "GAME_KEYBOARD_IntroToMainMenu", &GameStateIntro::mt_Continue, this);
	l_environement->m_event_manager.mt_Add_Callback(GameStateType::Intro, "GAME_GUI_IntroToMainMenu", &GameStateIntro::mt_Continue, this);
	l_environement->m_event_manager.mt_Add_Callback(GameStateType::Intro, "GAME_GUI_IntroQuit", &GameStateIntro::mt_Quit, this);

	m_text.setFont(m_Font);
	m_text.setString(sf::String(m_text_to_display));
	m_text.setCharacterSize(24);
}

void GameStateIntro::mt_OnExit(void)
{
	m_state_manager->mt_GetEnvironment()->m_texture_manager.mt_Release_Resource(m_texture_id);
	m_state_manager->mt_GetEnvironment()->m_event_manager.mt_Remove_Callback(GameStateType::Intro, "GAME_KEYBOARD_IntroToMainMenu");
}

void GameStateIntro::mt_Update(float update_data)
{
	//
}

void GameStateIntro::mt_Draw(void)
{
	sf::RenderWindow* l_window(m_state_manager->mt_GetEnvironment()->m_window.mt_Get_Renderer_Window());

	l_window->draw(m_sprite);
	l_window->draw(m_text);
}

void GameStateIntro::mt_Continue(EventDetails* detail)
{
	m_state_manager->mt_SetState(GameStateType::Game);
}

void GameStateIntro::mt_Quit(EventDetails* detail)
{
	m_state_manager->mt_GetEnvironment()->m_window.mt_On_Close(detail);
}