#ifndef _SYSTEM_STATE_HPP
#define _SYSTEM_STATE_HPP 1

#include "ECS_Core/ECS_System.hpp"

class SystemState : public ECS_System
{
public:
	SystemState(ECS_SystemManager* manager);

	virtual void mt_Notify(const ECS_EntityMessage& msg);
	virtual void mt_Update(float delta_time_ms);
	virtual void mt_Handle_Event(const ECS_EntityId& entity, const ECS_EntityEvent& event);

protected:

	void mt_Change_State(ECS_EntityId entity, ECS_EntityState state);
};

#endif // !_SYSTEM_STATE_HPP