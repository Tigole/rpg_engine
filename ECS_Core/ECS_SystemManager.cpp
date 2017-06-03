#include "ECS_SystemManager.hpp"

ECS_SystemManager::ECS_SystemManager()
 :	m_systems()
{
	//
}

void ECS_SystemManager::entityModified(const ECS_Entity& e, const ECS_ComponentContainer& owned_components)
{
	std::set<ECS_ComponentId> l_owned_components;

	for (auto& l_comp : owned_components)
	{
		l_owned_components.insert(l_comp.first);
	}

	for (auto& l_system : m_systems)
	{
		l_system.second->entityModified(e, l_owned_components);
	}
}
