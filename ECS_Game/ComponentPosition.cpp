#include "ComponentPosition.hpp"

#include <tinyxml.h>

ComponentPosition::Position::Position(int x, int y, int layer)
 :	m_x(x),
	m_y(y),
	m_layer(layer)
{}

ComponentPosition::ComponentPosition()
 :	ECS_Component(getComponentId()),
 	m_current_position(Position(0, 0, 0)),
	m_previous_position(Position(0, 0, 0))
{}

std::string ComponentPosition::getComponentId(void)
{
	return "ComponentPosition";
}

void ComponentPosition::load(const TiXmlElement& element)
{
	if (element.ValueStr() == getComponentId())
	{
		element.QueryIntAttribute("x", &m_current_position.m_x);
		element.QueryIntAttribute("y", &m_current_position.m_y);
		element.QueryIntAttribute("layer", &m_current_position.m_layer);
	}
}

void ComponentPosition::getCurrentPosition(Position& current_position)
{
	current_position = m_current_position;
}

void ComponentPosition::setCurrentPosition(const Position& current_position)
{
	m_previous_position = m_current_position;
	m_current_position = current_position;
}

void ComponentPosition::getPreviousPosition(Position& previous_position)
{
	previous_position = m_previous_position;
}

void ComponentPosition::moveBy(int dx, int dy, int d_layer)
{
	Position new_position(m_current_position.m_x + dx, m_current_position.m_y + dy, m_current_position.m_layer + d_layer);
	setCurrentPosition(new_position);
}
