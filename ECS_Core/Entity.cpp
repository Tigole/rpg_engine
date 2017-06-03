#include "Entity.hpp"
#include <tinyxml.h>

Entity::Entity()
	:m_id(0)
{}

Entity::~Entity()
{}

bool Entity::operator==(const Entity& other)
{
	return m_id == other.m_id;
}

void Entity::load(const TiXmlAttribute& attribute, EntityGenerator& entity_generator)
{
	int l_id;
	if ((attribute.NameTStr() == "entity_id") && (attribute.QueryIntValue(&l_id) == TIXML_SUCCESS))
	{
		m_id = (EntityId)l_id;
		entity_generator.add(m_id);
	}
}

void Entity::save(TiXmlAttribute& attribute)
{
	attribute.SetName("entity_id");
	attribute.SetIntValue(m_id);
}

EntityGenerator::EntityGenerator()
	:m_counter(1)
{}

bool EntityGenerator::generate(Entity& e)
{
	bool l_ret;

	if (e.m_id == 0)
	{
		e.m_id = getId();
		l_ret = true;
	}
	else
	{
		l_ret = false;
	}

	return l_ret;
}

EntityId EntityGenerator::getId()
{
	EntityId l_ret;
	if (m_removed_ids.empty())
	{
		l_ret = m_counter;
		m_counter++;
	}
	else
	{
		l_ret = m_removed_ids.back();
		m_removed_ids.pop_back();
	}
}

void EntityGenerator::remove(Entity& e)
{
	if (e.m_id != 0)
	{
		if (e.m_id == (m_counter - 1))
		{
			m_counter--;
		}
		else
		{
			m_removed_ids.push_back(e.m_id);
		}
	}	
}

void EntityGenerator::add(EntityId e)
{
	if (e == m_counter)
	{
		m_counter++;
	}
	else
	{
		std::find(m_removed_ids.begin(), m_removed_ids.end(), e);
	}
}