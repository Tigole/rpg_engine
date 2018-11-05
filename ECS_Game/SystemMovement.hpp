#ifndef _SYSTEM_MOVEMENT_HPP
#define _SYSTEM_MOVEMENT_HPP 1

#include "ECS_Core/ECS_System.hpp"

#include <SFML/System.hpp>

class ComponentMovable;
class BasicMap;

class SystemMovement : public ECS_System
{
public:
	SystemMovement(ECS_SystemManager* manager);

	void mt_Update(float delta_time_ms);

	void mt_Notify(const ECS_EntityMessage& msg);
	void mt_Handle_Event(const ECS_EntityId& entity, const ECS_EntityEvent& event);

	void mt_Set_Map(BasicMap* map);

private:
	void mt_Compute_Speed(float delta_time_ms, ComponentMovable& movable, const sf::Vector2f world_position);
	sf::Vector2f mt_Get_Tile_Friction(int elevation, int x_tile_index, int y_tile_index);

	void mt_Set_Direction(ECS_EntityId entity, Direction d);
	void mt_Stop_Entity(ECS_EntityId entity, Axis axis);

	BasicMap* m_p_map;
};

#endif // !_SYSTEM_MOVEMENT_HPP
