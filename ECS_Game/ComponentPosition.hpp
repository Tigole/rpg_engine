#ifndef _COMPONENT_POSITION_HPP
#define _COMPONENT_POSITION_HPP 1

#include "ECS_Core/ECS_Component.hpp"

#include <string>

class ComponentPosition : public ECS_Component
{
public:
	ComponentPosition();

	void load(const TiXmlElement& element);

	struct Position
	{
		Position(int x, int y, int layer = 0);
		int m_x;
		int m_y;
		int m_layer;
	};

	void getCurrentPosition(Position& current_position);
	void setCurrentPosition(const Position& current_position);
	void getPreviousPosition(Position& previous_position);

	void moveBy(int dx, int dy, int d_layer = 0);

	static std::string getComponentId(void);

protected:
	Position m_current_position;
	Position m_previous_position;
};

#endif // _COMPONENT_POSITION_HPP
