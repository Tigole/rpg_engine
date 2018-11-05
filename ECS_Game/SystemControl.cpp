#include "SystemControl.hpp"

#include "ECS_Game/ComponentPosition.hpp"
#include "ECS_Game/ComponentMovable.hpp"

#include "ECS_Core/ECS_SystemManager.hpp"
#include "ECS_Core/ECS_EntityManager.hpp"

SystemControl::SystemControl(ECS_SystemManager* manager)
	:ECS_System(ECS_SystemId::CONTROL, manager)
{
	//m_required_components.push_back(ECS_ComponentId::CONTROLLER);
	m_required_components.push_back(ECS_ComponentId::MOVABLE);
	m_required_components.push_back(ECS_ComponentId::POSITION);

	m_manager->mt_Get_MessageHandler()->mt_Add_Observer(ECS_EntityMessageId::MoveRqst, this);
	m_manager->mt_Get_MessageHandler()->mt_Add_Observer(ECS_EntityMessageId::StopMove, this);
}

void SystemControl::mt_Handle_Event(const ECS_EntityId& entity, const ECS_EntityEvent& event)
{
	/*switch (event)
	{
	case ECS_EntityEvent::MOVING_UP:
		mt_Move(entity, Direction::UP);
		break;
	case ECS_EntityEvent::MOVING_DOWN:
		mt_Move(entity, Direction::DOWN);
		break;
	case ECS_EntityEvent::MOVING_LEFT:
		mt_Move(entity, Direction::LEFT);
		break;
	case ECS_EntityEvent::MOVING_RIGHT:
		mt_Move(entity, Direction::RIGHT);
		break;
	default:
		break;
	}*/
}

void SystemControl::mt_Notify(const ECS_EntityMessage& msg)
{
	ECS_EntityManager* l_entity_mngr = m_manager->mt_Get_EntityManager();
	switch (msg.m_id)
	{
	case ECS_EntityMessageId::MoveRqst:
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

			mt_Move(msg.m_sender, msg.m_data.m_direction);

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
				mt_Stop(msg.m_sender, Axis::y);
			else
				mt_Stop(msg.m_sender, Axis::x);

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
	}
}

void SystemControl::mt_Update(float delta_time_ms)
{}

void SystemControl::mt_Move(ECS_EntityId entity, Direction d)
{
	ComponentMovable* l_movable = m_manager->mt_Get_EntityManager()->mt_Get_Component<ComponentMovable>(entity, ECS_ComponentId::MOVABLE);

	l_movable->mt_Move(d);
}

void SystemControl::mt_Stop(ECS_EntityId entity, Axis a)
{
	ComponentMovable* l_movable = m_manager->mt_Get_EntityManager()->mt_Get_Component<ComponentMovable>(entity, ECS_ComponentId::MOVABLE);

	l_movable->mt_Stop(a);
}