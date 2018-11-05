#include "SystemState.hpp"
#include "ECS_Core/ECS_SystemManager.hpp"

#include "ECS_Game/ComponentState.hpp"
#include "ECS_Game/ComponentMovable.hpp"
#include "ECS_Core/ECS_EntityManager.hpp"

SystemState::SystemState(ECS_SystemManager* manager)
	:ECS_System(ECS_SystemId::STATE, manager)
{
	m_required_components.push_back(ECS_ComponentId::STATE);
	m_required_components.push_back(ECS_ComponentId::MOVABLE);

	/*m_manager->mt_Get_MessageHandler()->mt_Add_Observer(ECS_EntityMessageId::MOVE, this);
	m_manager->mt_Get_MessageHandler()->mt_Add_Observer(ECS_EntityMessageId::SWITCH_STATE, this);*/
}

void SystemState::mt_Notify(const ECS_EntityMessage& msg)
{
	/*if (mt_Is_Registered(msg.m_sender))
	{
		switch (msg.m_id)
		{
		case ECS_EntityMessageId::MOVE:
		{
			ECS_EntityEvent l_event;
			ComponentState* l_state = m_manager->mt_Get_EntityManager()->mt_Get_Component<ComponentState>(msg.m_sender, ECS_ComponentId::STATE);

			if (msg.m_data.m_direction == Direction::DOWN)
				l_event = ECS_EntityEvent::MOVING_DOWN;
			else if (msg.m_data.m_direction == Direction::UP)
				l_event = ECS_EntityEvent::MOVING_UP;
			else if (msg.m_data.m_direction == Direction::RIGHT)
				l_event = ECS_EntityEvent::MOVING_RIGHT;
			else if (msg.m_data.m_direction == Direction::LEFT)
				l_event = ECS_EntityEvent::MOVING_LEFT;

			//m_manager->mt_Add_Event(msg.m_sender, l_event);

			mt_Change_State(msg.m_sender, ECS_EntityState::WALKING);
			break;
		}
		case ECS_EntityMessageId::STOP_MOVE:
		{
			ECS_EntityEvent l_event;
			ComponentMovable* l_mov = m_manager->mt_Get_EntityManager()->mt_Get_Component<ComponentMovable>(msg.m_sender, ECS_ComponentId::MOVABLE);

			if (msg.m_data.m_direction == Direction::DOWN)
				l_event = ECS_EntityEvent::MOVING_DOWN;
			else if (0)
			{
				ECS_EntityEvent::BECAME_IDLE;
				l_mov->mt_Get_Speed_px_per_ms().x;
			}
		}
		case ECS_EntityMessageId::SWITCH_STATE:
		{
			mt_Change_State(msg.m_sender, msg.m_data.m_state);
			break;
		}
		default:
			break;
		}
	}*/
}

void SystemState::mt_Update(float delta_time_ms)
{
	/*ECS_EntityMessage l_msg;
	ECS_MessageHandler* l_msg_handler = m_manager->mt_Get_MessageHandler();
	ECS_EntityManager* l_entity_mngr = m_manager->mt_Get_EntityManager();

	for (auto& entity : m_entities)
	{
		ComponentState* l_state = l_entity_mngr->mt_Get_Component<ComponentState>(entity, ECS_ComponentId::STATE);

		if (l_state->mt_Get_State() == ECS_EntityState::WALKING)
		{
			l_msg.m_id = ECS_EntityMessageId::IS_MOVING;
			l_msg.m_sender = entity;

			l_msg_handler->mt_Dispatch(l_msg);
		}
	}*/
}

void SystemState::mt_Handle_Event(const ECS_EntityId& entity, const ECS_EntityEvent& event)
{
	/*switch (event)
	{
	case ECS_EntityEvent::BECAME_IDLE:
		mt_Change_State(entity, ECS_EntityState::IDLE);
	default:
		break;
	}*/
}

void SystemState::mt_Change_State(ECS_EntityId entity, ECS_EntityState state)
{
	/*ComponentState* l_state = m_manager->mt_Get_EntityManager()->mt_Get_Component<ComponentState>(entity, ECS_ComponentId::STATE);
	ECS_EntityMessage l_msg;
	l_state->mt_Set_State(state);

	l_msg.m_id = ECS_EntityMessageId::STATE_CHANGED;
	l_msg.m_sender = entity;
	l_msg.m_data.m_state = state;

	m_manager->mt_Get_MessageHandler()->mt_Dispatch(l_msg);*/
}