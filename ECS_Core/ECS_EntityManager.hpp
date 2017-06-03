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
	ComponenetType* addComponent(const ECS_Entity& e, const ECS_ComponentId& c)
	{
		ECS_EntityContainer::iterator l_entity_it;
		ComponenetType* l_ret(nullptr);

		l_entity_it = m_entities.find(e);

		/** Add entity if it doesn't exists **/
		if (l_entity_it == m_entities.end())
		{
			l_entity_it = m_entities.emplace(e, nullptr).first;
		}

		if (l_entity_it != m_entities.end())
		{
			l_entity_it->second[c] = new ComponenetType();
			m_system_manager->entityModified(e, l_entity_it->second);
			l_ret = l_entity_it->second.at(c).get();
		}

		return l_ret;
	}

	void removeComponent(const ECS_Entity& e, const ECS_ComponentId& c)
	{
		ECS_EntityContainer::iterator l_entity_it;
		ECS_ComponentContainer::iterator l_component_it;

		l_entity_it = m_entities.find(e);

		if (l_entity_it != m_entities.end())
		{
			l_entity_it->second.erase(c);
		}
	}

	template<class ComponentType>
	ComponentType* getComponent(const ECS_Entity& e, const ECS_ComponentId& c)
	{
		ECS_EntityContainer::iterator l_entity_it;
		ECS_ComponentContainer::iterator l_component_it;
		ComponentType* l_ret(nullptr);

		l_entity_it = m_entities.find(e);

		if (l_entity_it != m_entities.end())
		{
			l_component_it = l_entity_it->second.find(c);
			if (l_component_it != l_entity_it->second.end())
			{
				l_ret = l_component_it->second;
			}
		}

		return l_ret;
	}

private:
	ECS_EntityContainer m_entities;
	ECS_SystemManager* m_system_manager;
};

#endif // !_ENTITY_MANAGER_HPP
