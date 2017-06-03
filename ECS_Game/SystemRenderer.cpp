#include "SystemRenderer.hpp"

ECS_SystemId SystemRenderer::getSystemId()
{
	return "SystemRenderer";
}

SystemRenderer::SystemRenderer(ECS_SystemManager* system_manager)
 :	ECS_System(getSystemId()),
	m_drawable_components()
{}

void SystemRenderer::notify(const ECS_EntityMessage& msg)
{

}
