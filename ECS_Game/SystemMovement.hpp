#ifndef _SYSTEM_MOVEMENT_HPP
#define _SYSTEM_MOVEMENT_HPP 1

#include "ECS_Core/ECS_System.hpp"

#include <SFML/System.hpp>

class ComponentMovable;
class BasicMap;

class SystemMovement : public ECS_System
{
public:
	SystemMovement();

	void mt_Update(float delta_time_ms);

	void mt_Notify(const ECS_EntityMessage& msg);

private:
	void mt_Compute_Speed(float delta_time_ms, ComponentMovable& movable, const sf::Vector2f world_position);
	sf::Vector2f mt_Get_Friction(int elevation, int x_tile_index, int y_tile_index);

	BasicMap* m_p_map;
};

#endif // !_SYSTEM_MOVEMENT_HPP
