#ifndef _ENTITY_HPP
#define _ENTITY_HPP 1

#include <vector>

class TiXmlAttribute;
class EntityGenerator;

using EntityId = uint32_t;

template<typename T>
class Bitset
{
public:
	//
private:
	T m_bits;
};

class Entity
{
public:
	Entity();
	~Entity();

	bool operator==(const Entity& other);
	void load(const TiXmlAttribute& attribute, EntityGenerator& entity_generator);
	void save(TiXmlAttribute& attribute);

private:
	friend EntityGenerator;

	EntityId m_id;
};

class EntityGenerator
{
public:
	EntityGenerator();
	bool generate(Entity& e);
	void remove(Entity& e);

private:
	friend Entity;
	void add(EntityId e);
	EntityId getId();
	EntityId m_counter;
	std::vector<EntityId> m_removed_ids;
};

#endif // !_ENTITY_HPP