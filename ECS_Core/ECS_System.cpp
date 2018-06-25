#include "ECS_System.hpp"
#include "ECS_Entity.hpp"

#include <algorithm>

ECS_System::ECS_System(const ECS_SystemId& system_id, ECS_SystemManager* manager)
 :	m_id(system_id),
	m_required_components(),
	m_entities(),
	m_manager(manager)
{}

ECS_System::~ECS_System()
{}

void ECS_System::mt_Add_Entity(const ECS_EntityId& entity)
{
	m_entities.push_back(entity);
}

void ECS_System::mt_Entity_Modified(const ECS_EntityId& e, const std::set<ECS_ComponentId>& owned_components)
{
	std::vector<ECS_EntityId>::iterator l_entity_it;

	l_entity_it = std::find(m_entities.begin(), m_entities.end(), e);

	/** 1. Entity was not known by the system but has now required components **/
	if (l_entity_it == m_entities.end())
	{
		if (mt_Is_Valid(owned_components) == true)
		{
			m_entities.push_back(e);
		}
	}
	/** 2. Entity was known by the system but does not have required components anymore **/
	else
	{
		if (mt_Is_Valid(owned_components) == false)
		{
			m_entities.erase(l_entity_it);
		}
	}
}

bool ECS_System::mt_Is_Valid(const std::set<ECS_ComponentId>& owned_components)
{
	size_t l_number_of_compliences(0);

	for (auto& r : m_required_components)
	{
		if (owned_components.find(r) != owned_components.end())
		{
			l_number_of_compliences++;
		}
	}

	return (l_number_of_compliences == m_required_components.size());
}
