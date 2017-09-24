#include "ComponentPosition.hpp"

#include <tinyxml.h>

const ECS_ComponentId& ComponentPosition::mt_Get_Component_Id(void)
{
	return ECS_ComponentId::POSITION;
}

void ComponentPosition::mt_Load(const TiXmlElement& element)
{
	/*if (element.ValueStr() == getComponentId())
	{
		element.QueryIntAttribute("x", &m_current_position.m_x);
		element.QueryIntAttribute("y", &m_current_position.m_y);
		element.QueryIntAttribute("layer", &m_current_position.m_layer);
	}*/
}

sf::Vector2f ComponentPosition::mt_Get_Current_Position(void)
{
	return m_current_world_position_px.first;
}

void ComponentPosition::mt_Set_Current_Position(const sf::Vector2f& new_world_position_px)
{
	m_previous_world_position_px.first = m_current_world_position_px.first;
	m_current_world_position_px.first = new_world_position_px;
}

void ComponentPosition::mt_Set_Current_Position(const sf::Vector2f& new_world_position_px, int new_layer)
{
	mt_Set_Current_Position(new_world_position_px);
	m_previous_world_position_px.second = m_current_world_position_px.second;
	m_current_world_position_px.second = new_layer;
}

sf::Vector2f ComponentPosition::mt_Get_Previous_Position(void)
{
	return m_previous_world_position_px.first;
}

void ComponentPosition::mt_Move_By(sf::Vector2f delta_px)
{
	mt_Set_Current_Position(m_current_world_position_px.first + delta_px);
}

void ComponentPosition::mt_Set_Layer(int layer)
{
	m_previous_world_position_px.second = m_current_world_position_px.second;
	m_current_world_position_px.second = layer;
}

int ComponentPosition::mt_Get_Current_Layer(void)
{
	return m_current_world_position_px.second;
}