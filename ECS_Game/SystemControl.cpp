#include "SystemControl.hpp"

SystemControl::SystemControl()
	:ECS_System(ECS_SystemId::CONTROL)
{
	m_required_components.push_back(ECS_ComponentId::CONTROLLER);
}

void SystemControl::mt_Handle_Event(const ECS_EntityId& entity, const ECS_EntityEvent& event)
{
	//
}