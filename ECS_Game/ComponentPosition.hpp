#ifndef _COMPONENT_POSITION_HPP
#define _COMPONENT_POSITION_HPP 1

#include "ECS_Core/ECS_Component.hpp"

#include <string>
#include <SFML/System/Vector2.hpp>

class ComponentPosition : public ECS_Component
{
public:
	ComponentPosition();
	
	sf::Vector2f mt_Get_Current_Position(void);
	int mt_Get_Current_Layer(void);
	sf::Vector2f mt_Get_Previous_Position(void);
	void mt_Set_Current_Position(const sf::Vector2f& new_world_position_px);
	void mt_Set_Current_Position(const sf::Vector2f& new_world_position_px, int new_layer);

	void mt_Move_By(sf::Vector2f delta_px);
	void mt_Set_Layer(int layer);

	static const ECS_ComponentId& mt_Get_Component_Id(void);

protected:
	std::pair<sf::Vector2f, int> m_current_world_position_px;
	std::pair<sf::Vector2f, int> m_previous_world_position_px;
};

#endif // _COMPONENT_POSITION_HPP
