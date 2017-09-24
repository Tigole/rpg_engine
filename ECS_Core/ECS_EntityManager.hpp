#ifndef _ENTITY_MANAGER_HPP
#define _ENTITY_MANAGER_HPP 1

#include "ECS_Entity.hpp"
#include "ECS_Component.hpp"
#include "ECS_Types.hpp"
#include "ECS_SystemManager.hpp"

class ECS_EntityManager
{
public:
	ECS_EntityManager(ECS_SystemManager& system_manager);

	template<class ComponenetType>
	ComponenetType* mt_Add_Component(const ECS_Entity& entity, const ECS_ComponentId& component_id)
	{
		ECS_EntityContainer::iterator l_entity_it;
		ComponenetType* l_ret(nullptr);

		l_entity_it = m_entities.find(entity);

		/** Add entity if it doesn't exists **/
		if (l_entity_it == m_entities.end())
		{
			l_entity_it = m_entities.emplace(entity, nullptr).first;
		}

		if (l_entity_it != m_entities.end())
		{
			l_entity_it->second[component_id] = new ComponenetType();
			m_system_manager->mt_Entity_Modified(entity, l_entity_it->second);
			l_ret = l_entity_it->second.at(component_id).get();
		}

		return l_ret;
	}

	void mt_Remove_Component(const ECS_Entity& entity, const ECS_ComponentId& component_id)
	{
		ECS_EntityContainer::iterator l_entity_it;
		ECS_ComponentContainer::iterator l_component_it;

		l_entity_it = m_entities.find(entity);

		if (l_entity_it != m_entities.end())
		{
			l_entity_it->second.erase(component_id);
		}
	}

	template<class ComponentType>
	ComponentType* mt_Get_Component(const ECS_Entity& entity, const ECS_ComponentId& component_id)
	{
		ECS_EntityContainer::iterator l_entity_it;
		ECS_ComponentContainer::iterator l_component_it;
		ComponentType* l_ret(nullptr);

		l_entity_it = m_entities.find(entity);

		if (l_entity_it != m_entities.end())
		{
			l_component_it = l_entity_it->second.find(component_id);
			if (l_component_it != l_entity_it->second.end())
			{
				l_ret = dynamic_cast<ComponentType*>(l_component_it->second.get());
			}
		}

		return l_ret;
	}

private:
	ECS_EntityContainer m_entities;
	ECS_SystemManager* m_system_manager;
};

#endif // !_ENTITY_MANAGER_HPP
