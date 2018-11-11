#ifndef _GAME_STATE_MAIN_MENU_HPP
#define _GAME_STATE_MAIN_MENU_HPP 1

#include "GameState.hpp"

#include <array>
#include <SFML/Graphics.hpp>

class ParticleEmitter;

enum class GameStateMainMenu_States
{
	Main,
	Options,
	Credits,
	Load,

	Count,
};

struct GameStateMainMenu_StateData
{
	std::string m_interface_id;
	std::string m_texture_id;
	sf::Sprite m_sprite;
	sf::Vector2i m_relativ_position;
};

class GameStateMainMenu : public GameState
{
public:
	GameStateMainMenu(GameStateManager* state_manager);

	virtual void mt_OnEntry(void);
	virtual void mt_OnExit(void);
	virtual void mt_Update(float update_data);
	virtual void mt_Draw(void);

	void mt_Play(EventDetails* detail);
	void mt_Load(EventDetails* detail);
	void mt_Options(EventDetails* detail);
	void mt_Credits(EventDetails* detail);
	void mt_Quit(EventDetails* detail);

protected:
	void mt_Change_State(GameStateMainMenu_States new_state);

	GameStateMainMenu_States m_current_state, m_previous_state;
	std::array<GameStateMainMenu_StateData, static_cast<std::size_t>(GameStateMainMenu_States::Count)> m_state_data;

	std::string m_music_id;
};

#endif // !_GAME_STATE_MAIN_MENU_HPP