#include "GameStateMainMenu.hpp"
#include "GameStateManager.hpp"
#include "Environment.hpp"

GameStateMainMenu::GameStateMainMenu(GameStateManager* state_manager)
	: GameState(state_manager),
	m_current_state(GameStateMainMenu_States::Count), m_previous_state(GameStateMainMenu_States::Count),
	m_music_id("Intro")
{
	m_state_data[static_cast<std::size_t>(GameStateMainMenu_States::Main)].m_texture_id = "MainMenu_Main";
	m_state_data[static_cast<std::size_t>(GameStateMainMenu_States::Main)].m_interface_id = "MainMenu_Main";
	m_state_data[static_cast<std::size_t>(GameStateMainMenu_States::Main)].m_relativ_position = { 0, 0 };
	m_state_data[static_cast<std::size_t>(GameStateMainMenu_States::Options)].m_texture_id = "MainMenu_Options";
	m_state_data[static_cast<std::size_t>(GameStateMainMenu_States::Options)].m_interface_id = "MainMenu_Main";
	m_state_data[static_cast<std::size_t>(GameStateMainMenu_States::Options)].m_relativ_position = { 0, -1 };
	m_state_data[static_cast<std::size_t>(GameStateMainMenu_States::Credits)].m_texture_id = "MainMenu_Credits";
	m_state_data[static_cast<std::size_t>(GameStateMainMenu_States::Credits)].m_interface_id = "MainMenu_Main";
	m_state_data[static_cast<std::size_t>(GameStateMainMenu_States::Credits)].m_relativ_position = { 0, 1 };
	m_state_data[static_cast<std::size_t>(GameStateMainMenu_States::Load)].m_texture_id = "MainMenu_Load";
	m_state_data[static_cast<std::size_t>(GameStateMainMenu_States::Load)].m_interface_id = "MainMenu_Main";
	m_state_data[static_cast<std::size_t>(GameStateMainMenu_States::Load)].m_relativ_position = { 1, 0 };

}

void GameStateMainMenu::mt_OnEntry(void)
{
	Environment* l_environement(m_state_manager->mt_GetEnvironment());

	mt_Change_State(GameStateMainMenu_States::Main);

	l_environement->m_event_manager.mt_Add_Callback(GameStateType::MainMenu, "GAME_KEYBOARD_MainMenuToGame", &GameStateMainMenu::mt_Play, this);
	l_environement->m_event_manager.mt_Add_Callback(GameStateType::MainMenu, "GAME_GUI_MainMenuToGame", &GameStateMainMenu::mt_Play, this);
	l_environement->m_event_manager.mt_Add_Callback(GameStateType::MainMenu, "GAME_GUI_MainMenuQuit", &GameStateMainMenu::mt_Quit, this);

	l_environement->m_sound_system.mt_Play_Music(m_music_id);

	auto l_window_size = l_environement->m_window.mt_Get_Renderer_Window()->getSize();
	for (std::size_t ii = 0; ii < l_window_size.x; ii += 20)
	{
		l_environement->m_particle_system.mt_Add_Emitter(GameStateType::MainMenu, "Intro", { static_cast<float>(ii), static_cast<float>(l_window_size.y + 15), 0}, 5, -1);
	}
}

void GameStateMainMenu::mt_OnExit(void)
{
	Environment* l_environement(m_state_manager->mt_GetEnvironment());

	mt_Change_State(GameStateMainMenu_States::Credits);	/** TODO : loading fail because state doesn't change when going back to the MainMenu state **/

	l_environement->m_event_manager.mt_Remove_Callback(GameStateType::MainMenu, "GAME_KEYBOARD_IntroToMainMenu");

	for (auto& l_state_data : m_state_data)
	{
		l_environement->m_texture_manager.mt_Release_Resource(l_state_data.m_texture_id);
	}

	l_environement->m_sound_system.mt_Stop_Music(m_music_id);
}

void GameStateMainMenu::mt_Update(float update_data)
{
	m_state_manager->mt_GetEnvironment()->m_particle_system.mt_Update(update_data);
#if 0
	if (m_previous_state != m_current_state)
	{
		if ((m_current_state < GameStateMainMenu_States::Count) && (m_previous_state < GameStateMainMenu_States::Count))
		{
			sf::Vector2f l_move;
			sf::View l_view(m_state_manager->mt_GetEnvironment()->m_window.mt_Get_Renderer_Window()->getView());

			l_move.x = 0.0f;
			l_move.y = 0.0f;

			if (1)
			{
				l_move.x = (m_state_data[static_cast<std::size_t>(m_current_state)].m_relativ_position.x - m_state_data[static_cast<std::size_t>(m_current_state)].m_relativ_position.x) / 1;
				l_move.y = (m_state_data[static_cast<std::size_t>(m_current_state)].m_relativ_position.y - m_state_data[static_cast<std::size_t>(m_current_state)].m_relativ_position.y) / 1;
			}

			l_view.move(l_move);

			m_state_manager->mt_GetEnvironment()->m_window.mt_Get_Renderer_Window()->setView(l_view);

			if (1)
			{
				m_previous_state = m_current_state;
			}
		}
	}
	else
	{
		//
	}
#endif
}

void GameStateMainMenu::mt_Draw(void)
{
	Window& l_window(m_state_manager->mt_GetEnvironment()->m_window);
	sf::RenderWindow* l_renderer(l_window.mt_Get_Renderer_Window());

	/*for (auto& l_state_data : m_state_data)
	{
		if (l_state_data.m_sprite.getGlobalBounds().intersects(l_window.mt_Get_View_Space()) == true)
		{
			l_renderer->draw(l_state_data.m_sprite);
		}
	}*/

	l_renderer->draw(m_state_data[static_cast<std::size_t>(m_current_state)].m_sprite);
	m_state_manager->mt_GetEnvironment()->m_particle_system.mt_Draw(*(m_state_manager->mt_GetEnvironment()->m_window.mt_Get_Renderer_Window()), 0);
}

void GameStateMainMenu::mt_Play(EventDetails* detail)
{
	m_state_manager->mt_SetState(GameStateType::Game);
}

void GameStateMainMenu::mt_Load(EventDetails* detail)
{
	//
}

void GameStateMainMenu::mt_Options(EventDetails* detail)
{
	//
}

void GameStateMainMenu::mt_Credits(EventDetails* detail)
{
	//
}

void GameStateMainMenu::mt_Quit(EventDetails* detail)
{
	m_state_manager->mt_GetEnvironment()->m_window.mt_On_Close(detail);
}

void GameStateMainMenu::mt_Change_State(GameStateMainMenu_States new_state)
{
	if (new_state != m_current_state)
	{
		sf::Texture* l_texture(nullptr);

		m_previous_state = m_current_state;
		m_current_state = new_state;

		l_texture = m_state_manager->mt_GetEnvironment()->m_texture_manager.mt_Get_Resource(m_state_data[static_cast<std::size_t>(m_current_state)].m_texture_id);

		if (l_texture != nullptr)
		{
			sf::Vector2f l_texture_scale(1.0f, 1.0f);
			auto l_texture_size = l_texture->getSize();
			auto l_window_size = m_state_manager->mt_GetEnvironment()->m_window.mt_Get_Renderer_Window()->getSize();
			m_state_data[static_cast<std::size_t>(m_current_state)].m_sprite.setTexture(*l_texture);

			if ((l_window_size.x != 0) && (l_window_size.y != 0))
			{
				l_texture_scale.x = static_cast<float>(l_window_size.x) / static_cast<float>(l_texture_size.x);
				l_texture_scale.y = static_cast<float>(l_window_size.y) / static_cast<float>(l_texture_size.y);
			}

			m_state_data[static_cast<std::size_t>(m_current_state)].m_sprite.setScale(l_texture_scale);
		}
	}
}
