#include "SystemSkeleton.hpp"
#include "ECS_Core/ECS_SystemManager.hpp"
#include "ECS_Core/ECS_EntityManager.hpp"
#include "ECS_Game/ComponentDrawableSkeleton.hpp"


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
	ECS_EntityManager* l_entity_manager(m_manager->mt_Get_EntityManager());
	ComponentDrawableSkeleton* l_entity_skeleton;

	for (auto& l_current_entity : m_entities)
	{
		l_entity_skeleton = l_entity_manager->mt_Get_Component<ComponentDrawableSkeleton>(l_current_entity, ECS_ComponentId::DRAW_SKELETON);
		auto l_animation_set = l_entity_skeleton->mt_Get_Animation();
		if (l_animation_set != nullptr)
		{
			for (auto& l_anim : *l_animation_set)
			{
				l_anim.second->mt_Update(delta_time_ms);
			}
		}
	}
}

void SystemSkeleton::mt_Handle_Event(const ECS_EntityId& entity, const ECS_EntityEvent& event)
{
	//
}

sf::Transform SystemSkeleton::mt_Get_Part_Transform(SkeletonData& part)
{
	return part.m_sprite.getTransform();
}