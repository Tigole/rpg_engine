#ifndef _GAME_STATE_INTRO_HPP
#define _GAME_STATE_INTRO_HPP 1
#if 0
#include "GameState.hpp"
#include <SFML/Graphics.hpp>

class EventDetails;

class GameStateIntro : public GameState
{
public:
	GameStateIntro(GameStateManager* state_manager);

	virtual void mt_OnEntry(void);
	virtual void mt_OnExit(void);
	virtual void mt_Update(float update_data);
	virtual void mt_Draw(void);

	void mt_Continue(EventDetails* detail);
	void mt_Quit(EventDetails* detail);

protected:
	sf::Font m_Font;
	sf::Sprite m_sprite;
	sf::Text m_text;

	std::string m_texture_id;
	std::string m_text_to_display;
};

#endif

#endif // !_GAME_STATE_INTRO_HPP