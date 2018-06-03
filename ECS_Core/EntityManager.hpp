#ifndef _ENTITY_MANAGER_HPP
#define _ENTITY_MANAGER_HPP 1

#include "Entity.hpp"
#include "IComponent.hpp"

#include <map>
#include <memory>

using ComponentId = uint32_t;

using ComponentContainer = std::map<ComponentId, std::unique_ptr<IComponent>>;
using EntityContainer = std::map<Entity, ComponentContainer>;

class EntityManager
{
public:
	//

	template<class ComponenetType>
	ComponenetType* addComponent(const Entity& e, const ComponentId& c)
	{
		EntityContainer::iterator l_entity_it;
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
			l_ret = l_entity_it->second.at(c).get();
		}

		return l_ret;
	}

private:
	EntityContainer m_entities;
};

#endif // !_ENTITY_MANAGER_HPP