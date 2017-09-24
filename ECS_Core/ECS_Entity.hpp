#ifndef _ECS_ENTITY_HPP
#define _ECS_ENTITY_HPP 1

#include "ECS_Types.hpp"

#include <vector>
#include <cstdint>

class TiXmlElement;
class ECS_EntityGenerator;
/*
class ECS_Entity
{
public:
	ECS_Entity();
	ECS_Entity(ECS_EntityGenerator& generator);
	~ECS_Entity();

	bool operator==(const ECS_Entity& other) const;
	bool operator<(const ECS_Entity& other) const;
	bool load(const TiXmlElement& element, ECS_EntityGenerator& entity_generator);
	void save(TiXmlElement& element);

private:
	friend ECS_EntityGenerator;
	static std::string ms_xml_attribute_name;

	ECS_EntityId m_id;
	ECS_EntityGenerator* m_generator;
};

class ECS_EntityGenerator
{
public:
	ECS_EntityGenerator();
	bool generate(ECS_Entity& e);
	void remove(ECS_Entity& e);

private:
	friend ECS_Entity;
	void add(ECS_EntityId e);
	ECS_EntityId getId();
	ECS_EntityId m_counter;
	std::vector<ECS_EntityId> m_removed_ids;
};*/

#endif // !_ECS_ENTITY_HPP
