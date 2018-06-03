#ifndef _GAME_STRING_HPP
#define _GAME_STRING_HPP 1

#include <string>
#include <unordered_set>
#include <unordered_map>

using GameStringArguments = std::unordered_map<std::string, std::string>;

class GameString
{
public:
	GameString(const std::string& sentence);
	std::string mt_Get_String(const GameStringArguments& args);

	void mt_Set(const std::string& sentence);
private:

	std::size_t mt_Parse_Arg(std::size_t start, std::string& ret, const GameStringArguments& args);

	std::string m_sentence;
};

#endif // !_GAME_STRING_HPP