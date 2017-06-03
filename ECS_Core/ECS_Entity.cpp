#include "ECS_Entity.hpp"
#include <tinyxml.h>

#include <algorithm>

std::string ECS_Entity::ms_xml_attribute_name("entity_id");

ECS_Entity::ECS_Entity()
 :	m_id(0),
	m_generator(nullptr)
{}

ECS_Entity::ECS_Entity(ECS_EntityGenerator& generator)
 :	m_id(0),
	m_generator(&generator)
{
	generator.generate(*this);
}

ECS_Entity::~ECS_Entity()
{
	if (m_generator != nullptr)
		m_generator->remove(*this);
}

bool ECS_Entity::operator==(const ECS_Entity& other) const
{
	return m_id == other.m_id;
}

bool ECS_Entity::operator<(const ECS_Entity& other) const
{
	return m_id < other.m_id;
}

bool ECS_Entity::load(const TiXmlElement& element, ECS_EntityGenerator& entity_generator)
{
	bool l_ret(false);
	int l_id;

	if ((m_id == 0) && (element.QueryIntAttribute(ms_xml_attribute_name, &l_id) == TIXML_SUCCESS))
	{
		l_ret = true;
		m_generator = &entity_generator;
		m_id = (ECS_EntityId)l_id;
		entity_generator.add(m_id);
	}

	return l_ret;
}

void ECS_Entity::save(TiXmlElement& element)
{
	element.SetAttribute(ms_xml_attribute_name, m_id);
}

ECS_EntityGenerator::ECS_EntityGenerator()
 :	m_counter(1),
	m_removed_ids(0)
{}

bool ECS_EntityGenerator::generate(ECS_Entity& e)
{
	bool l_ret;

	if (e.m_id == 0)
	{
		e.m_id = getId();
		e.m_generator = this;
		l_ret = true;
	}
	else
	{
		l_ret = false;
	}

	return l_ret;
}

ECS_EntityId ECS_EntityGenerator::getId()
{
	ECS_EntityId l_ret;

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

	return l_ret;
}

void ECS_EntityGenerator::remove(ECS_Entity& e)
{
	std::vector<ECS_EntityId>::iterator l_it;
	if (e.m_id != 0)
	{
		if (e.m_id == (m_counter - 1))
		{
			m_counter--;
			l_it = std::find(m_removed_ids.begin(), m_removed_ids.end(), m_counter);
			if (l_it != m_removed_ids.end())
				m_removed_ids.erase(l_it);
		}
		else
		{
			m_removed_ids.push_back(e.m_id);
		}
	}
}

void ECS_EntityGenerator::add(ECS_EntityId e)
{
	if (e == m_counter)
	{
		m_counter++;
	}
	else
	{
		for(ECS_EntityId id = m_counter; id <= e; id++)
			m_removed_ids.push_back(id);
		m_counter = e + 1;
	}
}
