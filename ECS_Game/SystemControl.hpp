#ifndef _SYSTEM_CONTROL_HPP
#define _SYSTEM_CONTROL_HPP 1

#include "ECS_Core/ECS_System.hpp"

class SystemControl : public ECS_System
{
public:
	SystemControl(ECS_SystemManager* manager);
	virtual void mt_Handle_Event(const ECS_EntityId& entity, const ECS_EntityEvent& event);
	virtual void mt_Notify(const ECS_EntityMessage& msg);
	virtual void mt_Update(float delta_time_ms);

protected:

	void mt_Move(ECS_EntityId entity, Direction d);
	void mt_Stop(ECS_EntityId entity, Axis a);
};

#endif // !_SYSTEM_CONTROL_HPP