#include "SystemMovement.hpp"
#include "Map/BasicMap.hpp"
#include "ECS_Core/ECS_EntityManager.hpp"
#include "Environment.hpp"
#include "ComponentMovable.hpp"
#include "ComponentPosition.hpp"

SystemMovement::SystemMovement()
	:ECS_System(ECS_SystemId::MOVEMENT), m_p_map(nullptr)
{
	m_required_components.push_back(ECS_ComponentId::MOVABLE);
	m_required_components.push_back(ECS_ComponentId::POSITION);
}

void SystemMovement::mt_Update(float delta_time_ms)
{
	if (m_p_map != nullptr)
	{
		ECS_EntityManager& l_entity_mngr(m_environment->m_entity_manager);
		for (const auto& l_entity : m_entities)
		{
			ComponentMovable* l_movable(l_entity_mngr.mt_Get_Component<ComponentMovable>(l_entity, ECS_ComponentId::MOVABLE));
			ComponentPosition* l_position(l_entity_mngr.mt_Get_Component<ComponentPosition>(l_entity, ECS_ComponentId::POSITION));
			mt_Compute_Speed(delta_time_ms, *l_movable, l_position->mt_Get_Current_Position());
			l_position->mt_Move_By(l_movable->mt_Get_Velocity_px_per_ms() * delta_time_ms);
		}
	}
}

void SystemMovement::mt_Notify(const ECS_EntityMessage& msg)
{
	//
}

void SystemMovement::mt_Compute_Speed(float delta_time_ms, ComponentMovable& movable, const sf::Vector2f world_position)
{
	sf::Vector2f l_friction_px_per_ms(0, 0);
	float l_magnitude_px_per_ms;

	l_friction_px_per_ms = sf::Vector2f(movable.mt_Get_Speed_px_per_ms().x * l_friction_px_per_ms.x, 
										movable.mt_Get_Speed_px_per_ms().y * l_friction_px_per_ms.y);

	movable.mt_Add_Velocity_px_per_ms(movable.mt_Get_Accelerationpx_per_ms2() * delta_time_ms);
	movable.mt_Set_Acceleration_px_per_ms2(sf::Vector2f(0.0f, 0.0f));
	movable.mt_Apply_Friction_px_per_ms(l_friction_px_per_ms * delta_time_ms);

	l_magnitude_px_per_ms = std::sqrt((movable.mt_Get_Velocity_px_per_ms().x * movable.mt_Get_Velocity_px_per_ms().x)
		+ (movable.mt_Get_Velocity_px_per_ms().y * movable.mt_Get_Velocity_px_per_ms().y));

	if (l_magnitude_px_per_ms > movable.mt_Get_Max_Velocity_px_per_ms())
	{
		movable.mt_Set_Velocity_px_per_ms(sf::Vector2f((movable.mt_Get_Velocity_px_per_ms().x / l_magnitude_px_per_ms) * movable.mt_Get_Max_Velocity_px_per_ms(),
			movable.mt_Get_Velocity_px_per_ms().y / l_magnitude_px_per_ms) * movable.mt_Get_Max_Velocity_px_per_ms());
	}
}

sf::Vector2f SystemMovement::mt_Get_Tile_Friction(int elevation, int x_tile_index, int y_tile_index)
{
	sf::Vector2f l_ret;
	
	l_ret.x = l_ret.y = m_p_map->mt_Get_Tile_Infos(x_tile_index, y_tile_index, elevation)->m_friction;

	return l_ret;
}

void SystemMovement::mt_Handle_Event(const ECS_EntityId& entity, const ECS_EntityEvent& event)
{
	//
}