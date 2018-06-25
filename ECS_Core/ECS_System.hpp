#ifndef _ISYSTEM_HPP
#define _ISYSTEM_HPP 1

#include "Observer/Observer.hpp"
#include "ECS_Types.hpp"
#include "ECS_Entity.hpp"

#include <string>
#include <vector>
#include <set>

class ECS_SystemManager;

class ECS_System : public Observer<ECS_EntityMessage>
{
public:
	ECS_System(const ECS_SystemId& system_id, ECS_SystemManager* manager);
	~ECS_System();

	void mt_Add_Entity(const ECS_EntityId& entity);
	void mt_Entity_Modified(const ECS_EntityId& entity, const std::set<ECS_ComponentId>& owned_components);
	virtual void mt_Update(float delta_time_ms) = 0;
	virtual void mt_Handle_Event(const ECS_EntityId& entity, const ECS_EntityEvent& event) = 0;

protected:
	virtual bool mt_Is_Valid(const std::set<ECS_ComponentId>& owned_components);

	ECS_SystemId m_id;
	std::vector<ECS_ComponentId> m_required_components;
	std::vector<ECS_EntityId> m_entities;
	ECS_SystemManager* m_manager;
};

#endif // !_ISYSTEM_HPP
