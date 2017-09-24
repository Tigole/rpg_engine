#ifndef _SYSTEM_MANAGER_HPP
#define _SYSTEM_MANAGER_HPP 1

#include <unordered_map>
#include <memory>
#include "ECS_System.hpp"
#include "ECS_Core/ECS_Types.hpp"

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
		if (l_system_it != m_systems.end())
		{
			m_systems[system_id] = new SystemType();
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

	void mt_Entity_Modified(const ECS_Entity& entity, const ECS_ComponentContainer& owned_components);

private:
	ECS_SystemContainer m_systems;
};

#endif // !_SYSTEM_MANAGER_HPP
