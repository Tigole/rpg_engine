#ifndef _ENTITY_MANAGER_HPP
#define _ENTITY_MANAGER_HPP 1

#include "ECS_Entity.hpp"
#include "ECS_Component.hpp"
#include "ECS_Types.hpp"
#include "ECS_SystemManager.hpp"

class XML_Element;
class TextureManager;

using EntityPathsContainer = std::unordered_map<std::string, std::string>;
using EntityStringConverter = std::unordered_map<std::string, ECS_EntityId>;

class ECS_EntityManager
{
public:
	ECS_EntityManager(const std::string& resource_path, ECS_SystemManager& system_manager, TextureManager* texture_manager);

	ECS_EntityId mt_Get_Entity(const std::string& id);
	ECS_EntityId mt_Add_Entity(const std::string& id);

	template<class ComponenetType>
	ComponenetType* mt_Add_Component(const ECS_EntityId& entity, const ECS_ComponentId& component_id)
	{
		ECS_EntityContainer::iterator l_entity_it;
		ComponenetType* l_ret(nullptr);

		l_entity_it = m_entities.find(entity);

		/** Add entity if it doesn't exists **/
		if (l_entity_it == m_entities.end())
		{
			l_entity_it = m_entities.emplace(entity, ECS_ComponentContainer()).first;
		}

		if (l_entity_it != m_entities.end())
		{
			l_ret = static_cast<ComponenetType*>(l_entity_it->second.emplace(component_id, new ComponenetType()).first->second.get());
			m_system_manager->mt_Entity_Modified(entity, l_entity_it->second);
		}

		return l_ret;
	}

	void mt_Remove_Component(const ECS_EntityId& entity, const ECS_ComponentId& component_id)
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
	ComponentType* mt_Get_Component(const ECS_EntityId& entity, const ECS_ComponentId& component_id)
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

	void mt_Load_Paths(const std::string& conf_file);

private:

	bool mt_Load_Entity(const XML_Element& entity);

	ECS_EntityContainer m_entities;
	ECS_SystemManager* m_system_manager;
	TextureManager* m_texture_manager;

	EntityPathsContainer m_paths;
	EntityStringConverter m_string_converter;

	std::string m_resource_path;
	ECS_EntityId m_current_id;
};

#endif // !_ENTITY_MANAGER_HPP
