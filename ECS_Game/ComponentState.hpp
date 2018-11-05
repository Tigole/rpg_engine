#ifndef _COMPONENT_STATE_HPP
#define _COMPONENT_STATE_HPP 1

#include "ECS_Core/ECS_Component.hpp"

class ComponentState : public ECS_Component
{
public:
	ComponentState();

	void mt_Set_State(const ECS_EntityState& state);
	ECS_EntityState mt_Get_State(void) const;

protected:
	ECS_EntityState m_state;
};

#endif // !_COMPONENT_STATE_HPP