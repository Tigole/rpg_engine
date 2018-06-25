#include "SystemControl.hpp"

#include "ECS_Game/ComponentPosition.hpp"


SystemControl::SystemControl(ECS_SystemManager* manager)
	:ECS_System(ECS_SystemId::CONTROL, manager)
{
	m_required_components.push_back(ECS_ComponentId::CONTROLLER);
}

void SystemControl::mt_Handle_Event(const ECS_EntityId& entity, const ECS_EntityEvent& event)
{
	/*ComponentPosition* l_position = 
	switch (event)
	{
	case ECS_EntityEvent::MOVING_UP:
		break;
	default:
		break;
	}*/
}