#include "ECS_System.hpp"
#include "ECS_Entity.hpp"

ECS_System::ECS_System(const ECS_SystemId& system_id)
 :	m_id(system_id),
	m_required_components(),
	m_entities()
{}

ECS_System::~ECS_System()
{}

void ECS_System::entityModified(const ECS_Entity& e, const std::set<ECS_ComponentId>& owned_components)
{
	std::set<ECS_Entity>::iterator l_entity_it;

	l_entity_it = m_entities.find(e);

	/** 1. Entity was not known by the system but has now required components **/
	if (l_entity_it == m_entities.end())
	{
		if (isValid(owned_components) == true)
		{
			m_entities.insert(e);
		}
	}
	/** 2. Entity was known by the system but does not have required components anymore **/
	else
	{
		if (isValid(owned_components) == false)
		{
			m_entities.erase(l_entity_it);
		}
	}
}

bool ECS_System::isValid(const std::set<ECS_ComponentId>& owned_components)
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
