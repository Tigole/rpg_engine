#ifndef _DIRECTION_HPP
#define _DIRECTION_HPP 1

#include <string>

enum class Direction
{
	Up = 0,
	Down,
	Left,
	Right
};

std::string fn_Direction_Enum_To_String(Direction d);
Direction fn_Direction_String_To_Enum(const std::string& d);

#endif // !_DIRECTION_HPP
