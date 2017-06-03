#ifndef _SYSTEM_RENDERER_HPP
#define _SYSTEM_RENDERER_HPP 1

#include "ECS_Core/ECS_System.hpp"

#include <vector>

class ECS_SystemManager;

class SystemRenderer : public ECS_System
{
public:
	SystemRenderer(ECS_SystemManager* system_manager);

	void notify(const ECS_EntityMessage& msg);

	static ECS_SystemId getSystemId();

private:
	std::vector<ECS_ComponentId> m_drawable_components;

};

#endif // _SYSTEM_RENDERER_HPP
