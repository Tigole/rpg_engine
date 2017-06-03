#ifndef _ISYSTEM_HPP
#define _ISYSTEM_HPP 1

#include "Observer/Observer.hpp"
#include "ECS_Types.hpp"
#include "ECS_Entity.hpp"

#include <string>
#include <vector>
#include <set>

class ECS_Entity;

class ECS_System : public Observer<ECS_EntityMessage>
{
public:
	ECS_System(const ECS_SystemId& system_id);
	~ECS_System();

	void entityModified(const ECS_Entity& e, const std::set<ECS_ComponentId>& owned_components);
	void update(float delta_time);

protected:
	virtual bool isValid(const std::set<ECS_ComponentId>& owned_components);

	ECS_SystemId m_id;
	std::vector<ECS_ComponentId> m_required_components;
	std::set<ECS_Entity> m_entities;
};

#endif // !_ISYSTEM_HPP
