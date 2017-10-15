#ifndef _SYSTEM_CONTROL_HPP
#define _SYSTEM_CONTROL_HPP 1

#include "ECS_Core/ECS_System.hpp"

class SystemControl : public ECS_System
{
	SystemControl();
	void mt_Handle_Event(const ECS_EntityId& entity, const ECS_EntityEvent& event);
};

#endif // !_SYSTEM_CONTROL_HPP