#ifndef _SYSTEM_MANAGER_HPP
#define _SYSTEM_MANAGER_HPP 1

#include <unordered_map>
#include <memory>
#include "ECS_System.hpp"
#include "ECS_Core/ECS_Types.hpp"
#include "EventQueue/EventQueue.hpp"

class ECS_EntityManager;
class Window;

class ECS_SystemManager
{
public:
	ECS_SystemManager();

	template<typename SystemType>
	SystemType* mt_Add_System(const ECS_SystemId& system_id)
	{
		SystemType* l_ret(nullptr);
		ECS_SystemContainer::iterator l_system_it;

		l_system_it = m_systems.find(system_id);
		if (l_system_it == m_systems.end())
		{
			m_systems[system_id] = std::make_unique<SystemType>(this);
		}

		return l_ret;
	}

	template<typename SystemType>
	SystemType* mt_Get_System(const ECS_SystemId& system_id)
	{
		SystemType* l_ret(nullptr);
		ECS_SystemContainer::iterator l_it;

		l_it = m_systems.find(system_id);
		if (l_it != m_systems.end())
		{
			l_ret = dynamic_cast<SystemType*>(l_it->second.get());
		}

		return l_ret;
	}

	void mt_Entity_Modified(const ECS_EntityId& entity, const ECS_ComponentContainer& owned_components);

	void mt_Add_Event(const ECS_EntityId& entity, const ECS_EntityEvent& event);

	void mt_Update(float delta_time_ms);

	void mt_Draw(Window& window, unsigned int layer);

	void mt_Set_EntityManager(ECS_EntityManager* manager);
	ECS_EntityManager* mt_Get_EntityManager(void);

private:
	void mt_Process_Events(void);

	ECS_EntityManager* m_entity_manager;
	ECS_SystemContainer m_systems;
	misc::UnorderedMap<ECS_EntityId, EventQueue<ECS_EntityEvent>> m_events_queue;
};

#endif // !_SYSTEM_MANAGER_HPP
