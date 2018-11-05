#include "SystemMovement.hpp"
#include "Map/BasicMap.hpp"
#include "ECS_Core/ECS_EntityManager.hpp"
#include "ECS_Core/ECS_SystemManager.hpp"
#include "Environment.hpp"
#include "ComponentMovable.hpp"
#include "ComponentPosition.hpp"

SystemMovement::SystemMovement(ECS_SystemManager* manager)
	:ECS_System(ECS_SystemId::MOVEMENT, manager), m_p_map(nullptr)
{
	m_required_components.push_back(ECS_ComponentId::MOVABLE);
	m_required_components.push_back(ECS_ComponentId::POSITION);

	m_manager->mt_Get_MessageHandler()->mt_Add_Observer(ECS_EntityMessageId::MoveRqst, this);
	m_manager->mt_Get_MessageHandler()->mt_Add_Observer(ECS_EntityMessageId::StopMove, this);
}

void SystemMovement::mt_Update(float delta_time_ms)
{
	if (m_p_map != nullptr)
	{
		ECS_EntityManager* l_entity_mngr(m_manager->mt_Get_EntityManager());
		for (const auto& l_entity : m_entities)
		{
			ComponentMovable* l_movable(l_entity_mngr->mt_Get_Component<ComponentMovable>(l_entity, ECS_ComponentId::MOVABLE));
			ComponentPosition* l_position(l_entity_mngr->mt_Get_Component<ComponentPosition>(l_entity, ECS_ComponentId::POSITION));
			mt_Compute_Speed(delta_time_ms, *l_movable, l_position->mt_Get_Current_Position());
			l_position->mt_Move_By(l_movable->mt_Get_Velocity() * delta_time_ms);
		}
	}
}

void SystemMovement::mt_Notify(const ECS_EntityMessage& msg)
{
	/*ECS_EntityManager* l_entity_mngr = m_manager->mt_Get_EntityManager();
	switch (msg.m_id)
	{
	case ECS_EntityMessageId::Move:
	{
		if (mt_Is_Registered(msg.m_sender))
		{
			ECS_EntityMessage l_msg;
			bool l_b_send_msg = false;
			ComponentMovable* l_movable = l_entity_mngr->mt_Get_Component<ComponentMovable>(msg.m_sender, ECS_ComponentId::MOVABLE);

			if (l_movable->mt_Get_Accelerationpx() == sf::Vector2f(0.0f, 0.0f))
			{
				l_b_send_msg = true;
				l_msg.m_sender = msg.m_sender;
				l_msg.m_id = ECS_EntityMessageId::StartMoving;
				l_msg.m_data.m_direction = msg.m_data.m_direction;
			}

			mt_Set_Direction(msg.m_sender, msg.m_data.m_direction);

			if (l_movable->mt_Get_Accelerationpx() == sf::Vector2f(0.0f, 0.0f))
			{
				l_b_send_msg = true;
				l_msg.m_sender = msg.m_sender;
				l_msg.m_id = ECS_EntityMessageId::StopMoving;
				l_msg.m_data.m_direction = msg.m_data.m_direction;
			}

			if (l_b_send_msg == true)
			{
				m_manager->mt_Get_MessageHandler()->mt_Dispatch(l_msg);
			}
		}
		break;
	}
	case ECS_EntityMessageId::StopMove:
	{
		if (mt_Is_Registered(msg.m_sender))
		{
			ECS_EntityMessage l_msg;
			bool l_b_send_msg = false;
			ComponentMovable* l_movable = l_entity_mngr->mt_Get_Component<ComponentMovable>(msg.m_sender, ECS_ComponentId::MOVABLE);

			if (msg.m_data.m_direction == Direction::Down || msg.m_data.m_direction == Direction::Up)
				mt_Stop_Entity(msg.m_sender, Axis::y);
			else
				mt_Stop_Entity(msg.m_sender, Axis::x);

			if (l_movable->mt_Get_Accelerationpx() == sf::Vector2f(0.0f, 0.0f))
			{
				l_b_send_msg = true;
				l_msg.m_sender = msg.m_sender;
				l_msg.m_id = ECS_EntityMessageId::StopMoving;
				l_msg.m_data.m_direction = msg.m_data.m_direction;
			}

			if (l_b_send_msg == true)
			{
				m_manager->mt_Get_MessageHandler()->mt_Dispatch(l_msg);
			}
		}
		break;
	}
	default:
		break;
	}*/
}

void SystemMovement::mt_Compute_Speed(float delta_time_ms, ComponentMovable& movable, const sf::Vector2f world_position)
{
	sf::Vector2f l_friction_px_per_ms(0, 0);
	float l_magnitude_px_per_ms;

	l_friction_px_per_ms = sf::Vector2f(movable.mt_Get_Speed().x * l_friction_px_per_ms.x, 
										movable.mt_Get_Speed().y * l_friction_px_per_ms.y);

	movable.mt_Add_Velocity(movable.mt_Get_Accelerationpx() * delta_time_ms);
	movable.mt_Set_Acceleration(sf::Vector2f(0.0f, 0.0f));
	movable.mt_Apply_Friction(l_friction_px_per_ms * delta_time_ms);

	l_magnitude_px_per_ms = std::sqrt((movable.mt_Get_Velocity().x * movable.mt_Get_Velocity().x)
		+ (movable.mt_Get_Velocity().y * movable.mt_Get_Velocity().y));

	if (l_magnitude_px_per_ms > movable.mt_Get_Max_Velocity())
	{
		movable.mt_Set_Velocity(sf::Vector2f((movable.mt_Get_Velocity().x / l_magnitude_px_per_ms) * movable.mt_Get_Max_Velocity(),
			(movable.mt_Get_Velocity().y / l_magnitude_px_per_ms) * movable.mt_Get_Max_Velocity()));
	}
}

sf::Vector2f SystemMovement::mt_Get_Tile_Friction(int elevation, int x_tile_index, int y_tile_index)
{
	sf::Vector2f l_ret(0.0f, 0.0f);
	const TileInfo* l_tile_infos(m_p_map->mt_Get_Tile_Infos(x_tile_index, y_tile_index, elevation));
	
	if (l_tile_infos != nullptr)
		l_ret = l_tile_infos->m_friction;

	return l_ret;
}

void SystemMovement::mt_Handle_Event(const ECS_EntityId& entity, const ECS_EntityEvent& event)
{
	/*switch (event)
	{
	case ECS_EntityEvent::COLLIDING_X:
		mt_Stop_Entity(entity, Axis::x);
		break;
	case ECS_EntityEvent::COLLIDING_Y:
		mt_Stop_Entity(entity, Axis::y);
		break;
	case ECS_EntityEvent::MOVING_LEFT:
		mt_Set_Direction(entity, Direction::LEFT);
		break;
	case ECS_EntityEvent::MOVING_RIGHT:
		mt_Set_Direction(entity, Direction::RIGHT);
		break;
	case ECS_EntityEvent::MOVING_DOWN:
		mt_Set_Direction(entity, Direction::DOWN);
		break;
	case ECS_EntityEvent::MOVING_UP:
		mt_Set_Direction(entity, Direction::UP);
		break;
	default:
		break;
	}*/
}

void SystemMovement::mt_Set_Direction(ECS_EntityId entity, Direction d)
{
	ECS_EntityMessage l_msg;
	ComponentMovable* l_movable = m_manager->mt_Get_EntityManager()->mt_Get_Component<ComponentMovable>(entity, ECS_ComponentId::MOVABLE);
	
	l_movable->mt_Set_Direction(d);

	l_msg.m_id = ECS_EntityMessageId::DirectionChanged;
	l_msg.m_sender = entity;
	l_msg.m_data.m_direction = d;

	m_manager->mt_Get_MessageHandler()->mt_Dispatch(l_msg);
}

void SystemMovement::mt_Stop_Entity(ECS_EntityId entity, Axis axis)
{
	ComponentMovable* l_movable = m_manager->mt_Get_EntityManager()->mt_Get_Component<ComponentMovable>(entity, ECS_ComponentId::MOVABLE);

	if (axis == Axis::x)
		l_movable->mt_Set_Velocity(sf::Vector2f(0.0f, l_movable->mt_Get_Velocity().y));
	else if (axis == Axis::y)
		l_movable->mt_Set_Velocity(sf::Vector2f(l_movable->mt_Get_Velocity().x, 0.0f));
}

void SystemMovement::mt_Set_Map(BasicMap* map)
{
	m_p_map = map;
}