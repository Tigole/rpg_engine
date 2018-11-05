#ifndef _GAME_STATE_TYPES_HPP
#define _GAME_STATE_TYPES_HPP 1

#include <string>

enum class GameStateType
{
	/*SplashScreen = 0,
	Intro,*/
	MainMenu,
	Game,

	COUNT
};

GameStateType fn_GameStateType_ToEnum(const std::string& type);
std::string fn_GameStateType_ToString(const GameStateType& type);

#endif // !_GAME_STATE_TYPES_HPP