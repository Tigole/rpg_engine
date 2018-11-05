#include "SystemSkeleton.hpp"


SystemSkeleton::SystemSkeleton(ECS_SystemManager* manager)
	:ECS_System(ECS_SystemId::SKELETON, manager)
{
	m_required_components.push_back(ECS_ComponentId::DRAW_SKELETON);
	m_required_components.push_back(ECS_ComponentId::STATE);
}

void SystemSkeleton::mt_Notify(const ECS_EntityMessage& msg)
{
	//
}

void SystemSkeleton::mt_Update(float delta_time_ms)
{
	//
}

void SystemSkeleton::mt_Handle_Event(const ECS_EntityId& entity, const ECS_EntityEvent& event)
{
	//
}