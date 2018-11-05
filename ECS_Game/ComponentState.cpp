#include "ComponentState.hpp"

ComponentState::ComponentState()
	:ECS_Component(ECS_ComponentId::STATE),
	m_state(ECS_EntityState::IDLE)
{}

void ComponentState::mt_Set_State(const ECS_EntityState& state)
{
	m_state = state;
}

ECS_EntityState ComponentState::mt_Get_State(void) const
{
	return m_state;
}
