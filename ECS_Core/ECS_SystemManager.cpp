#include "ECS_SystemManager.hpp"
#include "ECS_EntityManager.hpp"
#include "ECS_Game/SystemRenderer.hpp"

#include <iostream>

ECS_SystemManager::ECS_SystemManager()
 :	m_systems()
{
	//
}

void ECS_SystemManager::mt_Entity_Modified(const ECS_EntityId& entity, const ECS_ComponentContainer& owned_components)
{
	std::set<ECS_ComponentId> l_owned_components;

	for (auto& l_comp : owned_components)
	{
		l_owned_components.insert(l_comp.first);
	}

	for (auto& l_system : m_systems)
	{
		l_system.second->mt_Entity_Modified(entity, l_owned_components);
	}
}

void ECS_SystemManager::mt_Add_Event(const ECS_EntityId& entity, const ECS_EntityEvent& event)
{
	m_events_queue[entity].mt_Add_Event(event);
}

void ECS_SystemManager::mt_Update(float delta_time_ms)
{
	for (auto& l_system : m_systems)
	{
		l_system.second->mt_Update(delta_time_ms);
	}
	mt_Process_Events();
}

void ECS_SystemManager::mt_Process_Events(void)
{
	for (auto& l_entity_event_queue : m_events_queue)
	{
		ECS_EntityEvent l_entity_event;
		while (l_entity_event_queue.second.mt_Process(l_entity_event) == true)
		{
			std::cout << "Evt: " << fn_ECS_EntityEvent_Enum_To_String(l_entity_event) << '\n';
			for (auto& l_system : m_systems)
			{
				l_system.second->mt_Handle_Event(l_entity_event_queue.first, l_entity_event);
			}
		}
	}
}

void ECS_SystemManager::mt_Draw(Window& window, unsigned int layer)
{
	auto l_it(m_systems.find(ECS_SystemId::RENDERER));

	if (l_it != m_systems.end())	
	{
		SystemRenderer* l_syst_renderer(dynamic_cast<SystemRenderer*>(l_it->second.get()));

		l_syst_renderer->mt_Render(window, layer);
	}
}

void ECS_SystemManager::mt_Set_EntityManager(ECS_EntityManager* manager)
{
	m_entity_manager = manager;
}

ECS_EntityManager* ECS_SystemManager::mt_Get_EntityManager(void)
{
	return m_entity_manager;
}

ECS_MessageHandler* ECS_SystemManager::mt_Get_MessageHandler(void)
{
	return &m_message_handler;
}